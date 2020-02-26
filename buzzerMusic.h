/*
 * buzzerMusic.h
 *
 * Created: 13/11/2017 21:48:33
 *  Author: Lucas Seara Manoel
 */ 
#include "defPrincipais.h"

#ifndef BUZZERMUSIC_H_
#define BUZZERMUSIC_H_

#define  FALSE 0

#define C6_NOTE_US	1911
#define CS6_NOTE_US 1804
#define D6_NOTE_US	1703
#define DS6_NOTE_US 1607
#define E6_NOTE_US	1517
#define F6_NOTE_US	1432
#define FS6_NOTE_US 1351
#define G6_NOTE_US	1276
#define GS6_NOTE_US 1204
#define A6_NOTE_US	1136
#define AS6_NOTE_US 1073
#define B6_NOTE_US	1012

#define C0_NOTE_US	30578
#define CS0_NOTE_US 28862
#define D0_NOTE_US	27242
#define DS0_NOTE_US 25713
#define E0_NOTE_US	24270
#define F0_NOTE_US	22908
#define FS0_NOTE_US 21622
#define G0_NOTE_US	20408
#define GS0_NOTE_US 19263
#define A0_NOTE_US	18181
#define AS0_NOTE_US 17161
#define B0_NOTE_US	16198

#define C4_NOTE_F  261.62557 // Hz
#define CS4_NOTE_F 277.18263 // Hz
#define D4_NOTE_F  293.66477 // Hz
#define DS4_NOTE_F 311.12698 // Hz
#define E4_NOTE_F  329.62756 // Hz
#define F4_NOTE_F  349.22823 // Hz
#define FS4_NOTE_F 369.99442 // Hz
#define G4_NOTE_F  391.99544 // Hz
#define GS4_NOTE_F 415.3047 // Hz
#define A4_NOTE_F  440 // Hz
#define AS4_NOTE_F 466.16376 // Hz
#define B4_NOTE_F  493.8833 // Hz

#define C4_NOTE_P  (1/C4_NOTE_F) // segundos
#define CS4_NOTE_P (1/CS4_NOTE_F) // segundos
#define D4_NOTE_P  (1/D4_NOTE_F) // segundos
#define DS4_NOTE_P (1/DS4_NOTE_F) // segundos
#define E4_NOTE_P  (1/E4_NOTE_F) // segundos
#define F4_NOTE_P  (1/F4_NOTE_F) // segundos
#define FS4_NOTE_P (1/FS4_NOTE_F) // segundos
#define G4_NOTE_P  (1/G4_NOTE_F) // segundos
#define GS4_NOTE_P (1/GS4_NOTE_F) // segundos
#define A4_NOTE_P  (1/A4_NOTE_F) // segundos
#define AS4_NOTE_P (1/AS4_NOTE_F) // segundos
#define B4_NOTE_P  (1/B4_NOTE_F) // segundos


#define C4_NOTE_CLOCK1	80306 // 261.62557 Hz
#define CS4_NOTE_CLOCK1 75798 // 277.18263 Hz
#define D4_NOTE_CLOCK1	71544 // 293.66477 Hz
#define DS4_NOTE_CLOCK1 67529 // 311.12698 Hz
#define E4_NOTE_CLOCK1	63739 // 329.62756 Hz
#define F4_NOTE_CLOCK1	60161 // 349.22823 Hz
#define FS4_NOTE_CLOCK1 56785 // 369.99442 Hz
#define G4_NOTE_CLOCK1	53598 // 391.99544 Hz
#define GS4_NOTE_CLOCK1 50589 // 415.3047 Hz
#define A4_NOTE_CLOCK1	47750 // 440 Hz
#define AS4_NOTE_CLOCK1 45070 // 466.16376 Hz
#define B4_NOTE_CLOCK1	42540 // 493.8833 Hz
#define COMPASSO_CLOCK1 32768/8
#define INFINITO_CLOCK1 0xFFFFFFF0

#define N_FREQ_NOTES 13

typedef enum note_freq{
	__NOTE = 0,
	C_NOTE,//1
	CS_NOTE,//2
	D_NOTE,//3
	DS_NOTE,//4
	E_NOTE,//5
	F_NOTE,//6
	FS_NOTE,//7
	G_NOTE,//8
	GS_NOTE,//9
	A_NOTE,//10
	AS_NOTE,//11
	B_NOTE,//12
	O_NOTE
}note_freq;

#define OITAVA_0 1
#define OITAVA_1 2
#define OITAVA_2 4
#define OITAVA_3 8
#define OITAVA_4 16
#define OITAVA_5 32
#define OITAVA_6 64
#define OITAVA_7 128
#define OITAVA_8 256
#define OITAVA_9 512
	
#define N_TEMPO_NOTES 6
typedef enum note_tempo{
	SEMI_BREVE = 32,
	MINIMA = 16,
	SEMINIMA = 8,
	COLCHEIA = 4,
	SEMI_COLCHEIA = 2,
	FUSA = 1
}note_tempo;

//Estrutura de um tema musical:-------------------
typedef struct _note_sequencer
{
	note_freq* note_freq_vector;//Vetor contendo a sequencia de notas musicais do tema	
	uint32_t n_note;//Marcador de nota
}note_sequencer;

typedef struct _music_sequencer
{
	bool_t loop_mode;//Faz o tema musical ser tocado repedidamente.
	note_sequencer* note_sequence_vector;//Sequencia de notas
	uint32_t n_sequence;//Marcador de sequencia para música com multiplas sequencias
}music_sequencer;
//------------------------------------------------	

void inic_TC0();//Inicializa o timer gerador do sinal.

//Funções de uso interno do sistema:--------------
void play_note();
void play_time();
void next_sequence();
//------------------------------------------------

//Temas criados-----------------------------------
//Para se criar um tema musical é preciso criar uma função
//de inicialização e uma função para disparar a música. 
//Exemplos:
void init_tema_1();
void play_tema_1();

void init_tema_2();
void play_tema_2();

void init_tema_3();
void play_tema_3();
//------------------------------------------------

//Efeitos Sonoros---------------------------------
void init_sound_getBonus();
void play_sound_getBonus();

void init_sound_damaged();
void play_sound_damaged();
//------------------------------------------------
#endif /* BUZZERMUSIC_H_ */