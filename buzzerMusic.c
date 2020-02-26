/*
 * buzzerMusic.c
 *
 * Created: 13/11/2017 21:48:57
 *  Author: Lucas Seara Manoel
 */ 

#include "buzzerMusic.h"

music_sequencer*  music_sequencer_buffer;

uint32_t note_count=0, compass_count=0;

// Tema 1: ----------------------------------------------------------------------
//-------------------------------------------------------------------------------

note_freq  tema_1_compass_freq_1[32] =   {F_NOTE, O_NOTE, O_NOTE, O_NOTE, G_NOTE, O_NOTE, O_NOTE, O_NOTE,
										  F_NOTE, E_NOTE, O_NOTE, O_NOTE, G_NOTE, E_NOTE, O_NOTE, O_NOTE,
										  F_NOTE, E_NOTE, E_NOTE, O_NOTE, G_NOTE, E_NOTE, E_NOTE, O_NOTE,
										  F_NOTE, E_NOTE, E_NOTE, E_NOTE, G_NOTE, E_NOTE, E_NOTE, E_NOTE};									

note_freq  tema_1_compass_freq_2[32] =    {E_NOTE, E_NOTE, E_NOTE, E_NOTE, A_NOTE, E_NOTE, E_NOTE, G_NOTE,
										   E_NOTE, E_NOTE, __NOTE, __NOTE, G_NOTE, E_NOTE, E_NOTE, E_NOTE,
										   E_NOTE, E_NOTE, E_NOTE, E_NOTE, A_NOTE, E_NOTE, E_NOTE, G_NOTE,
										   E_NOTE, E_NOTE, __NOTE, __NOTE, G_NOTE, E_NOTE, E_NOTE, E_NOTE};
											
note_freq  tema_1_compass_freq_3[32] =    {F_NOTE, E_NOTE, E_NOTE, E_NOTE, G_NOTE, E_NOTE, E_NOTE, A_NOTE,
										   B_NOTE, E_NOTE, E_NOTE, B_NOTE, A_NOTE, E_NOTE, E_NOTE, A_NOTE,
										   G_NOTE, E_NOTE, E_NOTE, G_NOTE, F_NOTE, E_NOTE, E_NOTE, F_NOTE,
										   E_NOTE, E_NOTE, E_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,};

note_freq  tema_1_compass_freq_4[32] ={E_NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE,
									   __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE,
									   __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE,
									   __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE, __NOTE};


#define N_SEQ_TEMA_1 4
music_sequencer tema_1;
note_sequencer sequence_tema_1[N_SEQ_TEMA_1];

void init_tema_1()
{		
	sequence_tema_1[0].note_freq_vector = tema_1_compass_freq_1;
	sequence_tema_1[0].n_note= 32;
	
	sequence_tema_1[1].note_freq_vector = tema_1_compass_freq_2;
	sequence_tema_1[1].n_note= 32;
	
	sequence_tema_1[2].note_freq_vector = tema_1_compass_freq_3;
	sequence_tema_1[2].n_note= 32;
	
	sequence_tema_1[3].note_freq_vector = tema_1_compass_freq_4;
	sequence_tema_1[3].n_note= 32;
	
	tema_1.note_sequence_vector=sequence_tema_1; 
	tema_1.n_sequence = N_SEQ_TEMA_1;
	
	tema_1.loop_mode = FALSE;
}

void play_tema_1()
{	
	music_sequencer_buffer = &tema_1;
	
	TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)	
}

// Tema 2: ----------------------------------------------------------------------
//-------------------------------------------------------------------------------

note_freq  tema_2_compass_freq_1[32] =     {G_NOTE, E_NOTE, E_NOTE, D_NOTE, F_NOTE, E_NOTE, E_NOTE, G_NOTE,
											A_NOTE, E_NOTE, E_NOTE, D_NOTE, G_NOTE, E_NOTE, E_NOTE, F_NOTE,
											G_NOTE, E_NOTE, E_NOTE, D_NOTE, F_NOTE, E_NOTE, E_NOTE, G_NOTE,
											A_NOTE, E_NOTE, E_NOTE, D_NOTE, G_NOTE, E_NOTE, E_NOTE, F_NOTE};

note_freq  tema_2_compass_freq_2[32] =     {E_NOTE, G_NOTE, A_NOTE, E_NOTE, E_NOTE, A_NOTE, B_NOTE, E_NOTE,
											E_NOTE, G_NOTE, A_NOTE, E_NOTE, E_NOTE, A_NOTE, B_NOTE, E_NOTE,
											D_NOTE, __NOTE, __NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, __NOTE,
											E_NOTE, __NOTE, __NOTE, D_NOTE, E_NOTE, __NOTE, __NOTE, __NOTE};

note_freq  tema_2_compass_freq_3[32] =    {D_NOTE, __NOTE, __NOTE, D_NOTE, E_NOTE, __NOTE, F_NOTE, GS_NOTE,
										   AS_NOTE, B_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,
										   E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,
										   E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE};

note_freq  tema_2_compass_freq_4[32] =	{E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,
										 E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,
										 E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE,
										 E_NOTE, O_NOTE, O_NOTE, D_NOTE, E_NOTE, O_NOTE, E_NOTE, O_NOTE};


#define N_SEQ_TEMA_2 4
music_sequencer tema_2;
note_sequencer sequence_tema_2[N_SEQ_TEMA_2];

void init_tema_2()
{
	sequence_tema_2[0].note_freq_vector = tema_2_compass_freq_1;
	sequence_tema_2[0].n_note= 32;
	
	sequence_tema_2[1].note_freq_vector = tema_2_compass_freq_2;
	sequence_tema_2[1].n_note= 32;
	
	sequence_tema_2[2].note_freq_vector = tema_2_compass_freq_3;
	sequence_tema_2[2].n_note= 32;
	
	sequence_tema_2[3].note_freq_vector = tema_2_compass_freq_4;
	sequence_tema_2[3].n_note= 32;
	
	tema_2.note_sequence_vector=sequence_tema_2;
	tema_2.n_sequence = N_SEQ_TEMA_2;
	
	tema_2.loop_mode = FALSE;
}

void play_tema_2()
{
	music_sequencer_buffer = &tema_2;
	
	TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
}

// Tema 3: ----------------------------------------------------------------------
//-------------------------------------------------------------------------------
note_freq  tema_3_compass_freq_1[32] =     {E_NOTE, O_NOTE, O_NOTE, E_NOTE, O_NOTE, O_NOTE, E_NOTE, D_NOTE,
											E_NOTE, O_NOTE, O_NOTE, E_NOTE, E_NOTE, O_NOTE, E_NOTE, C_NOTE,
											E_NOTE, O_NOTE, O_NOTE, E_NOTE, O_NOTE, O_NOTE, E_NOTE, D_NOTE,
											E_NOTE, O_NOTE, O_NOTE, E_NOTE, E_NOTE, E_NOTE, O_NOTE, D_NOTE};


#define N_SEQ_TEMA_3 1
music_sequencer tema_3;
note_sequencer sequence_tema_3[N_SEQ_TEMA_3];

void init_tema_3()
{
	sequence_tema_3[0].note_freq_vector = tema_3_compass_freq_1;
	sequence_tema_3[0].n_note= 32;
		
	tema_3.note_sequence_vector=sequence_tema_3;
	tema_3.n_sequence = N_SEQ_TEMA_3;
	
	tema_3.loop_mode = FALSE;
}

void play_tema_3()
{
	music_sequencer_buffer = &tema_3;
	
	TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
}

// Efeitos Sonoros - getBonus: --------------------------------------------------
//-------------------------------------------------------------------------------
note_freq  tema_getBonus_compass_freq[4] = {A_NOTE, A_NOTE, A_NOTE, B_NOTE};

#define N_SEQ_TEMA_GETBONUS 1
music_sequencer tema_getBonus;
note_sequencer sequence_tema_getBonus[N_SEQ_TEMA_GETBONUS];

void init_sound_getBonus()
{
	sequence_tema_getBonus[0].note_freq_vector = tema_getBonus_compass_freq;
	sequence_tema_getBonus[0].n_note= 4;
	
	tema_getBonus.note_sequence_vector=sequence_tema_getBonus;
	tema_getBonus.n_sequence = N_SEQ_TEMA_GETBONUS;
	
	tema_getBonus.loop_mode = FALSE;
}

void play_sound_getBonus()
{
	music_sequencer_buffer = &tema_getBonus;
		
	TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
}

// Efeitos Sonoros - damaged: ---------------------------------------------------
//-------------------------------------------------------------------------------
note_freq  tema_damaged_compass_freq[2] = {C_NOTE, CS_NOTE};

#define N_SEQ_TEMA_DAMAGED 1
music_sequencer tema_damaged;
note_sequencer sequence_tema_damaged[N_SEQ_TEMA_DAMAGED];

void init_sound_damaged()
{
	sequence_tema_damaged[0].note_freq_vector = tema_damaged_compass_freq;
	sequence_tema_damaged[0].n_note= 2;
	
	tema_damaged.note_sequence_vector=sequence_tema_damaged;
	tema_damaged.n_sequence = N_SEQ_TEMA_GETBONUS;
	
	tema_damaged.loop_mode = FALSE;	
}

void play_sound_damaged()
{
	music_sequencer_buffer = &tema_damaged;
		
	TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
}

//-------------------------------------------------------------------------------
void play_note()
{		
	if(music_sequencer_buffer->note_sequence_vector[compass_count].note_freq_vector[note_count])
	{			
		switch(music_sequencer_buffer->note_sequence_vector[compass_count].note_freq_vector[note_count])//compass_freq[note_count]
		{
			case __NOTE:
				break;
			case C_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = C4_NOTE_CLOCK1;
				break;
			case CS_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = CS4_NOTE_CLOCK1;
				break;
			case D_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = D4_NOTE_CLOCK1;
				break;
			case DS_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = DS4_NOTE_CLOCK1;
				break;
			case E_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = E4_NOTE_CLOCK1;
				break;
			case F_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = F4_NOTE_CLOCK1;
				break;
			case FS_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = FS4_NOTE_CLOCK1;	
				break;
			case G_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = G4_NOTE_CLOCK1;
				break;
			case GS_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = GS4_NOTE_CLOCK1;
				break;
			case A_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = A4_NOTE_CLOCK1;
				break;
			case AS_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = AS4_NOTE_CLOCK1;
				break;
			case B_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = B4_NOTE_CLOCK1;
				break;
			case O_NOTE:
				TC0->TC_CHANNEL[1].TC_RC = INFINITO_CLOCK1;
				break;
		}		
		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)	
	}
}

void play_time()
{		
	play_note();
	
	note_count++;
	if(note_count >= music_sequencer_buffer->note_sequence_vector[compass_count].n_note)
	{
		note_count = 0;
		next_sequence();
	}
}

void next_sequence()
{
	compass_count++;
	if(compass_count >= music_sequencer_buffer->n_sequence)
	{
		if(music_sequencer_buffer->loop_mode)
		{
			compass_count = 0;
			TC0->TC_CHANNEL[0].TC_RC = COMPASSO_CLOCK1;
			TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
		}
		else
		{
			TC0->TC_CHANNEL[0].TC_RC = INFINITO_CLOCK1;
			TC0->TC_CHANNEL[1].TC_RC = INFINITO_CLOCK1;
			TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
			TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;// Reset counter (SWTRG) and enable counter clock (CLKEN)
			compass_count = 0;
		}
	}	
}

