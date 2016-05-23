#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define HEADER_SIZE 16
#define CHR_ROM_SIZE (8*1024)
#define PRG_ROM_SIZE (16*1024)
#define TRAINER_SIZE 512

unsigned char chr_rom_data[CHR_ROM_SIZE] = {0};

int main(int argc, char *argv[])
{
  FILE* ines_file = NULL;

  if( argc > 1 ) {
    fprintf(stderr, "Usage: %s\n\n", argv[0]);
    fprintf(stderr, "This program reads an NES file and parses the header informaion.\n");
    fprintf(stderr, "This program takes no arguments.\n");
    fprintf(stderr, "The NES file is read from stdin.\n");
    fprintf(stderr, "The header information is written to stdout.\n");
    exit(-1);
  }

  /* ines_file = fopen(ines_filename_arg, "r"); */
  ines_file = stdin;
  if( ines_file == NULL ) {
    fprintf(stderr, "Error: Could not open NES file for reading\n");
    goto error_cleanup_exit;
  }

  /* Read the header. */
  {
    unsigned char header[HEADER_SIZE];
    size_t bytes_read;
    unsigned char flags6;
    unsigned char flags7;
    unsigned char flags9;

    bytes_read = fread(header,1,HEADER_SIZE,ines_file);
    if( bytes_read != HEADER_SIZE ) {
      fprintf(stderr, "Error: Could not read NES file header.\n");
      goto error_cleanup_exit;
    }
    if( header[0] != 0x4E
        || header[1] != 0x45
        || header[2] != 0x53
        || header[3] != 0x1A ) {
      fprintf(stderr, "Error: No valid NES header found.\n");
      goto error_cleanup_exit;
    }
    flags6 = header[6];
    flags7 = header[7];
    flags9 = header[9];

    if( 2 == ((flags7 & 0x0c) >> 2) ) {
      fprintf(stdout,
             "The file is in NES 2.0 format.\n");
    } else {
      fprintf(stdout,
              "This file is in NES 1.0 format.\n");
    }


    fprintf(stdout, "Size of PRG ROM in 16KB units: %u\n", (unsigned int)header[4]);
    fprintf(stdout,
            "Size of CHR ROM in 8KB units (0 means CHR-RAM is used): %u\n",
            (unsigned int)header[5]);
    fprintf(stdout,
            "Size of PRG RAM in 8KB units (0 infers 8KB for compatibility): %u\n",
            (unsigned int)header[8]);
    fprintf(stdout,
            "Mapper number: %u\n",
            (unsigned int)((flags7 & 0xF0) | ((flags6 & 0xF0)>>4)));

    if( flags6 & 0x08 ) {
      fprintf(stdout,
              "Nametable mirroring: four-screen.\n");
    } else {
      if( flags6 & 0x01 ) {
        fprintf(stdout,
                "Nametable mirroring: horizontal arrangement / vertical mirroring.\n");
      } else {
        fprintf(stdout,
                "Nametable mirroring: vertical arrangment /  horizontal mirroring.\n");
      }
    }

    if( flags6 & 0x2 ) {
      fprintf(stdout,
              "SRAM at 6000-7FFFh is battery backed.\n");
    } else {
      fprintf(stdout,
              "SRAM at 6000-7FFFh is NOT battery backed.\n");
    }

    if( flags6 & 0x4 ) {
      fprintf(stdout,
              "512 byte trainer at 7000-71FFh.\n");
    } else {
      fprintf(stdout,
              "No trainer present.\n");
    }

    if( flags7 & 0x1 ) {
      fprintf(stdout,
              "VS Unisystem Game.\n");
    } else {
      fprintf(stdout,
              "Not a VS Unisystem Game.\n");
    }

    if( flags7 & 0x2 ) {
      fprintf(stdout,
              "PlayChoice-10 Game (8KB of Hint Screen data stored after CHR data).\n");
    } else {
      fprintf(stdout,
              "Not a PlayChoice-10 Game.\n");
    }

    if( 2 == ((flags7 & 0x08) >> 2) ) {
    } else {
      if( flags9 & 0x1 ) {
        fprintf(stdout,
                "This is a PAL rom.\n");
      } else {
        fprintf(stdout,
                "This is an NTSC rom.\n");
      }
    }
  }
  goto success_cleanup_exit;


success_cleanup_exit:
  return 0;

error_cleanup_exit:
  return -1;
}
