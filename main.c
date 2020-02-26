/***************************************************************************************
*		Frogger RTOS
*		Jogo feito em RTOS onde um sapo tenta atravessar varias estradas rumo a segurança
*		Utiliza LCD5110 e um Joystick
*
*		Aluno: Daniel Pereira
*		Data de criação: 12/09/2018	v. 2.0
*		Data de apresentação: 04/12/2018
*		Disciciplina: Microcontroladores 2
*		Professor: Charles Borges
*
*		Versão 4.0
***************************************************************************************/

#include "defPrincipais.h"
#include "figuras.h"
#include "buzzerMusic.h"
#include "NOKIA5110_fb.h"
#include "atraso.h"
#include "ADC.h"
#include "buzzerMusic.h"

#define max_cars	12

static uint32_t media_eixoX, media_eixoY;
static uint32_t carsXY[max_cars][2];
static struct pontos_t setting_stndr;
static struct pontos_t frog_position;
static struct pontos_t cars_position;
static char movment = 1;
static int8_t kick=0;					//Reponsavel por resetar a posição do frogger
static int8_t lose=0;					//
static int8_t wins=0;
static int8_t hits=3;					//Utilizado para o frogger não ser instantaneamente derrotado
static int8_t c_id=0;					//Utilizado para o documentar cada veiculo

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

void vTask_LCD(void *pvParameters)
{
	while(1)
	{
		imprime_LCD();
	}
}

void vTask_Joystick(void *pvParameters)
{
	static uint32_t ADC_x[32], ADC_y[32], k=0;
	uint32_t j;
	
	while(1)
	{
		ADC_Handler();		// le o ADC, atualiza x e y
		
		ADC_x[k] = get_ADC_VRx();  //valor do ADC entra no filtro, na amostra mais antiga
		ADC_y[k] = get_ADC_VRy();
		
		k++; if(k==32) k=0;
		
		media_eixoX = 0;
		media_eixoY = 0;
		
		for(j=0; j<32; j++)
		{
			media_eixoX += ADC_x[j];  //somatório das amostras e média
			media_eixoY += ADC_y[j];
		}
		media_eixoX /= 32;
		media_eixoY /= 32;
	}
}

void vTask_Fields(void *pvParameters)
{
	struct pontos_t p_c;
	
	p_c.x1 = 0; p_c.y1 = 0;

	while(1)
	{
		p_c.x1 = 7; p_c.y1 = 0;
		p_c.x2 = 7; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		p_c.x1 = 18; p_c.y1 = 0;
		p_c.x2 = 18; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		p_c.x1 = 29; p_c.y1 = 0;
		p_c.x2 = 29; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		p_c.x1 = 40; p_c.y1 = 0;
		p_c.x2 = 40; p_c.y2 = 48;
		desenha_linha(&p_c,1);

		p_c.x1 = 51; p_c.y1 = 0;
		p_c.x2 = 51; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		p_c.x1 = 62; p_c.y1 = 0;
		p_c.x2 = 62; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		p_c.x1 = 73; p_c.y1 = 0;
		p_c.x2 = 73; p_c.y2 = 48;
		desenha_linha(&p_c,1);
		
		
		desenha_pixel(18,10,0);
		desenha_pixel(18,11,0);
		desenha_pixel(29,10,0);
		desenha_pixel(29,11,0);
		desenha_pixel(40,10,0);
		desenha_pixel(40,11,0);
		desenha_pixel(29,10,0);
		desenha_pixel(29,11,0);
		desenha_pixel(51,10,0);
		desenha_pixel(51,11,0);
		desenha_pixel(62,10,0);
		desenha_pixel(62,11,0);
		desenha_pixel(18,21,0);
		desenha_pixel(18,22,0);
		desenha_pixel(29,21,0);
		desenha_pixel(29,22,0);
		desenha_pixel(40,21,0);
		desenha_pixel(40,22,0);
		desenha_pixel(29,21,0);
		desenha_pixel(29,22,0);
		desenha_pixel(51,21,0);
		desenha_pixel(51,22,0);
		desenha_pixel(62,21,0);
		desenha_pixel(62,22,0);
		desenha_pixel(18,32,0);
		desenha_pixel(18,33,0);
		desenha_pixel(29,32,0);
		desenha_pixel(29,33,0);
		desenha_pixel(40,32,0);
		desenha_pixel(40,33,0);
		desenha_pixel(29,32,0);
		desenha_pixel(29,33,0);
		desenha_pixel(51,32,0);
		desenha_pixel(51,33,0);
		desenha_pixel(62,32,0);
		desenha_pixel(62,33,0);
		
		
		vTaskDelay(ms(300));
		
	}
}

void vTask_Frogger(void *pvParameters)
{
	static uint32_t x = 0, y = 19;
	static int32_t dif_eixoX, dif_eixoY;
	
	frog_position.x2 = 0; frog_position.y2 = 0;
	frog_position.x3 = 0; frog_position.y3 = 0;
	
	while(1)
	{
		dif_eixoX = 512 - media_eixoX;
		dif_eixoY = 512 - media_eixoY;
		
		if(kick==1){kick=0; x=0; y=19;}
		
		if(dif_eixoX < -50)
		{
			if(x>=0 && x<76) x++;
			movment = 1;					//Sapo indo para direita
		}
		else if(dif_eixoX > 50)				// 50 = Delta de tolerancia no deslocamento do eixo
		{
			if(x<=76 && x>0) x--;
			movment = 0;					//Sapo indo para esquerda
		}
		
		// ------------------------------------------------------------------------
		if(dif_eixoY < -50)
		{
			if(y<=39 && y>0) y--;
		}
		
		else if(dif_eixoY > 50)
		{
			if(y>=0 && y<39) y++;
		}
		
		// ------------------------------------------------------------------------
		frog_position.x1 = x;  frog_position.y1 = y;
		
		if (movment==0)
		{
			
			desenha_fig(&frog_position,&frog_r);
			vTaskDelay(ms(150));					// Atraso para controle da velocidade do sapo
			desenha_fig(&frog_position,&delete_frog);
		}
		else
		{
			desenha_fig(&frog_position,&frog_l);
			vTaskDelay(ms(150));					// Atraso para controle da velocidade do sapo
			desenha_fig(&frog_position,&delete_frog);
		}
	}

}

void  vTask_C_Cars(void *pvParameters)
{
	uint8_t n=0, local=0, low=0;
	
	while(1)
	{
		while(c_id<max_cars-1)
		{
			cars_position.x1 = 9;  carsXY[0][0] =  cars_position.x1;		//Carro 1 - Lane 1
			cars_position.y1 = 0;  carsXY[0][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 9;  carsXY[1][0] =  cars_position.x1;		//Carro 2 - Lane 1
			cars_position.y1 = 20; carsXY[1][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------			
			cars_position.x1 = 20; carsXY[2][0] =  cars_position.x1;		//Carro 1 - Lane 2
			cars_position.y1 = 39; carsXY[2][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 20; carsXY[3][0] =  cars_position.x1;		//Carro 2 - Lane 2
			cars_position.y1 = 20; carsXY[3][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------			
			cars_position.x1 = 31; carsXY[4][0] =  cars_position.x1;		//Carro 1 - Lane 3
			cars_position.y1 = 0;  carsXY[4][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 31; carsXY[5][0] =  cars_position.x1;		//Carro 2 - Lane 3
			cars_position.y1 = 20; carsXY[5][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------			
			cars_position.x1 = 42; carsXY[6][0] =   cars_position.x1;		//Carro 1 - Lane 4
			cars_position.y1 = 39; carsXY[6][1] =   cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 42; carsXY[7][0]  = cars_position.x1;		//Carro 2 - Lane 4
			cars_position.y1 = 20; carsXY[7][1]  = cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------	
			cars_position.x1 = 53; carsXY[8][0] =   cars_position.x1;		//Carro 1 - Lane 5
			cars_position.y1 = 0;  carsXY[8][1] =   cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 53; carsXY[9][0]  = cars_position.x1;		//Carro 2 - Lane 5
			cars_position.y1 = 20; carsXY[9][1]  = cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------
			cars_position.x1 = 64; carsXY[10][0] =  cars_position.x1;		//Carro 1 - Lane 6
			cars_position.y1 = 39; carsXY[10][1] =  cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
			
			cars_position.x1 = 64; carsXY[11][0] = cars_position.x1;		//Carro 2 - Lane 6
			cars_position.y1 = 20; carsXY[11][1] = cars_position.y1;
			desenha_fig(&cars_position, &car_d); c_id++;
//---------------------------------------------------------------------------------------------------				
		}
		
	}
}

void vTask_Move_C(void *pvParameters)
{
	uint8_t i=0, moves=0;
	
	while(1)
	{
		if((carsXY[i][0]%2)==1)
		{
			cars_position.x1 = carsXY[i][0];
			cars_position.y1 = carsXY[i][1];
			desenha_fig(&cars_position, &delete_car);
			
			if((carsXY[i][1]+1) >= 40){carsXY[i][1]=0;}
			else{carsXY[i][1]  = carsXY[i][1]  +  1;}
				
			cars_position.y1 = carsXY[i][1];
			desenha_fig(&cars_position, &car_d);
		}
		
		else if((carsXY[i][0]%2)==0)
		{
			cars_position.x1 = carsXY[i][0];
			cars_position.y1 = carsXY[i][1];
			desenha_fig(&cars_position, &delete_car);
			
			if((carsXY[i][1]-1) <= 0){carsXY[i][1]=39;}
			else{carsXY[i][1]  = carsXY[i][1]  -  1;}
			
			cars_position.y1 = carsXY[i][1];
			desenha_fig(&cars_position, &car_u);
		}
		
		i++;
		
		if(i>=max_cars){i=0;}
		
		vTaskDelay(ms(10));
	}
	
}

void vTask_Damage(void *pvParameters)
{
	uint8_t i=0;

	struct pontos_t p;
	
	p.x1 = 0; p.y1 = 0;
	p.x2 = 0; p.y2 = 0;
	p.x3 = 0; p.y3 = 0;
	
	while(1)
	{
		i=0;
		while(i<c_id)
		{
			if (movment)
			{
				if ( ((frog_position.y1+1)>=carsXY[i][1]) && ((frog_position.y1+1)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+5)>=carsXY[i][0]) && ((frog_position.x1+5)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
				else if ( ((frog_position.y1+3)>=carsXY[i][1]) && ((frog_position.y1+3)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+1)>=carsXY[i][0]) && ((frog_position.x1+1)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
				else if ( ((frog_position.y1+3)>=carsXY[i][1]) && ((frog_position.y1+3)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+3)>=carsXY[i][0]) && ((frog_position.x1+3)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
			}
			else
			{
				if ( ((frog_position.y1+1)>=carsXY[i][1]) && ((frog_position.y1+1)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+1)>=carsXY[i][0]) && ((frog_position.x1+1)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
				else if ( ((frog_position.y1+3)>=carsXY[i][1]) && ((frog_position.y1+3)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+6)>=carsXY[i][0]) && ((frog_position.x1+6)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
				else if ( ((frog_position.y1+3)>=carsXY[i][1]) && ((frog_position.y1+3)<=(carsXY[i][1]+8)))
				{
					if ( ((frog_position.x1+3)>=carsXY[i][0]) && ((frog_position.x1+3)<=(carsXY[i][0]+7))){ hits=hits-1;}
				}
				
			}

			i++;
		}

		if (hits==0)
		{
			kick = 1;
			hits = 3;
			lose = 1;
		}
		
		if (frog_position.x1 >=73)
		{
			kick = 1;
			hits = 3;
			wins = 1;
		}
		vTaskDelay(ms(500));
	}
}

void  vResults_Final(void *pvParameters)
{
	setting_stndr.x1 = 0; setting_stndr.y1 = 0;
	
	while(1)
	{	
		if(lose==1)
		{
			vTaskPrioritySet(vResults_Final, 4);
			desenha_fig(&setting_stndr, &tela_game_over);
			atraso_ms(500);
			
			if((PIOA->PIO_PDSR & PIO_PA23))
			{
				vTaskPrioritySet(vResults_Final, 1);
				lose = 0;
			}	
		}
		
		if(wins==1)
		{
			vTaskPrioritySet(vResults_Final, 4);
			desenha_fig(&setting_stndr, &tela_victory);
			atraso_ms(500);
			
			if((PIOA->PIO_PDSR & PIO_PA23))
			{
				vTaskPrioritySet(vResults_Final, 1);
				wins = 0;
			}
		}
	}
}

int main (void)
{
	sysclk_init();
	
	WDT->WDT_MR = WDT_MR_WDDIS;		//desabilitar o watchdog!
	
	// Sound Configurations ---------------------------------------------------------------------------
	inic_TC0();
	init_tema_1();//Inicialização dos temas musicais que poderão ser acionados ao longo do programa.
	
	// --------------------------------------------------------------------------------------
	// Botao Joystik  pino PA23 - A2 (Arduino)
	PIOA->PIO_PER =  PIO_PA23;			// PIO Enable Register
	PIOA->PIO_PUER = PIO_PA23;			// Pull-up Enable Register (DEFAULT É HABILITADO)
	PIOA->PIO_ODR =  PIO_PA23;			// Output Disable Register (DEFAULT É DESABILITADO)

	// Habilita o Debouncing por hardware
	PIOA->PIO_DIFSR= PIO_PA23;	// Debouncing Input Filter Select Register
	PIOA->PIO_IFER = PIO_PA23;	// Glitch Input Filter Enable Register 
	PIOA->PIO_SCDR = 163;		/* ajuste do divisor de clock para o debouncing filter
									DIV = (T/(2.Tslow)) - 1
									[Slow Clock = 32768 Hz] clock para o sistema
									[T = 10 ms] período do debauncing - validade garantida para pulso > T
								*/
	//Reading the I/O line levels requires the clock of the PIO controller to be enabled
	PMC->PMC_PCER0 = 0x01 << ID_PIOA;
	
	// Gerador de Números Aleatórios do ATSAM
	pmc_enable_periph_clk(ID_TRNG);	// liga o ckl para o TRNG
	TRNG->TRNG_CR = 0x524E4701;		// habilita o TRNG
	
	// --------------------------------------------------------------------------------------
	inic_ADC();
	//inic_Interrupt_ADC_EOC();
	// --------------------------------------------------------------------------------------
	// inicializa LCD 5110   
	inic_IO_LCD();					// CLK (13 - PB27), DIN (12 - PD8), DC (11 - PD7), CE (10 - PC29), RST (9 - PC21)
	inic_LCD();
	limpa_LCD();
	// --------------------------------------------------------------------------------------
	// inicializa tela do jogo
	escreve2fb(tela_inicial_1);
	imprime_LCD();
	
	while((PIOA->PIO_PDSR & PIO_PA23)) // quando pressionar a tecla começa o jogo
	{
		atraso_ms(350);
		escreve2fb(tela_inicial_2);
		imprime_LCD();
		atraso_ms(350);
		escreve2fb(tela_inicial_3);
		imprime_LCD();
		atraso_ms(350);
		escreve2fb(tela_inicial_4);
		imprime_LCD();
	}	
	
	limpa_LCD();
	// ---------------------------------------------------------------------------------------

	// cria as tarefas
	xTaskCreate(vTask_LCD,		"Task 0", 200, NULL, 1,NULL);
	xTaskCreate(vTask_Joystick,	"Task 1", 200, NULL, 1, NULL);
	xTaskCreate(vTask_Fields,	"Task 2", 200, NULL, 1, NULL);
	xTaskCreate(vTask_Frogger,	"Task 3", 200, NULL, 1, NULL);
	xTaskCreate(vTask_C_Cars,	"Task 4", 200, NULL, 1, NULL);
	xTaskCreate(vTask_Move_C,	"Task 5", 200, NULL, 1, NULL);
	xTaskCreate(vTask_Damage,	"Task 6", 200, NULL, 1, NULL);
	xTaskCreate(vResults_Final,	"Task 6", 200, NULL, 1, NULL);
	
	vTaskStartScheduler();	// apos este comando o RTOS passa a executar as tarefas

	while(1);
}
//---------------------------------------------------------------------------------------------------

void TC0_Handler(void)
{
	TC0->TC_CHANNEL[0].TC_SR;							// Clear status register
	
	play_time();
}

void TC1_Handler(void)
{
	TC0->TC_CHANNEL[1].TC_SR;							// Clear status register
	
	if(PIOB->PIO_ODSR & PIO_PB25)				// lê o valor escrito no pino e faz uma máscara com o bit 27 (pino PB27), se for '1' limpa, senao ativa pino PB27
	PIOB->PIO_CODR = PIO_PB25;				// Clear Output Data Register
	else
	PIOB->PIO_SODR = PIO_PB25;				// Set Output Data Register
}

void TC2_Handler(void)
{
	TC0->TC_CHANNEL[2].TC_SR;							// Clear status register
}

//---------------------------------------------------------------------------------------------
void inic_TC0()
{
	PMC->PMC_PCER0 = (1 << ID_TC0)|(1 << ID_TC1);					// Enable the TC0 clock (27 ch 0, 28 ch 1, 29 ch 2)
	
	TC0->TC_CHANNEL[0].TC_SR;												// Clear status register
	TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_CPCTRG | TC_CMR_TCCLKS_TIMER_CLOCK5;	// RC Compare Trigger Enable e selecao do TIMER_CLOCK5 (FCPU/2)
	TC0->TC_CHANNEL[0].TC_RC = INFINITO_CLOCK1;										// Compare Value = 200ms
	
	TC0->TC_CHANNEL[1].TC_SR;													// Clear status register
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_CPCTRG | TC_CMR_TCCLKS_TIMER_CLOCK1;	// RC Compare Trigger Enable e selecao do TIMER_CLOCK5 (SCLK - 32768Hz)
	TC0->TC_CHANNEL[1].TC_RC = INFINITO_CLOCK1;										// Compare Value = 1 s
	
	TC0->TC_CHANNEL[2].TC_SR;													// Clear status register
	TC0->TC_CHANNEL[2].TC_CMR = TC_CMR_CPCTRG | TC_CMR_TCCLKS_TIMER_CLOCK1;	// RC Compare Trigger Enable e selecao do TIMER_CLOCK5 (SCLK - 32768Hz)
	TC0->TC_CHANNEL[2].TC_RC = INFINITO_CLOCK1;										// Compare Value = 1 s
	
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);										// Configure and enable interrupt on RC compare
	NVIC_EnableIRQ((IRQn_Type) ID_TC1);										// Configure and enable interrupt on RC compare

	TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;								// Interruption on RC Compare
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;				// Reset counter (SWTRG) and enable counter clock (CLKEN)
	
	TC0->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;								// Interruption on RC Compare
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;				// Reset counter (SWTRG) and enable counter clock (CLKEN)
	
	TC0->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;								// Interruption on RC Compare
	TC0->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;				// Reset counter (SWTRG) and enable counter clock (CLKEN)

	PIOB->PIO_PER = PIO_PB25;		// PIO Enable Register - habilita o pino PB27 (13 no Arduino due) conectado ao LED da placa
	PIOB->PIO_OER = PIO_PB25;		// Output Enable Register
	PIOB->PIO_PUDR = PIO_PB25;		// Pull-up Disable Register - desabilita pull-up do pino PB27
}