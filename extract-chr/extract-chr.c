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
  int chr_rom_index;
  FILE* ines_file = NULL;
  char *chr_rom_index_arg;
  int trainer_count;
  int chr_rom_count;
  int prg_rom_count;

  if( argc > 2 ) {
    fprintf(stderr,"Usage: %s [CHR-ROM index]\n\n", argv[0]);
    fprintf(stderr,"The program extracts a single 8KB CHR-ROM segment from an iNES file.\n");
    fprintf(stderr,"The CHR-ROM index is optional. The default index is 0.\n");
    fprintf(stderr,"The iNES file is read from stdin.\n");
    fprintf(stderr,"The CHR-ROM data is written to stdout.\n");
    exit(-1);
  }

  /* ines_filename_arg = argv[1]; */
  if( argc == 2 ) {
    chr_rom_index_arg = argv[1];
  } else {
    chr_rom_index_arg = "0";
  }

  chr_rom_index = atoi(chr_rom_index_arg);
  if( chr_rom_index < 0 ) {
    fprintf(stderr, "Error: CHR-ROM index is negative: %s\n", chr_rom_index_arg);
    goto error_cleanup_exit;
  }

  /* ines_file = fopen(ines_filename_arg, "r"); */
  ines_file = stdin;
  if( ines_file == NULL ) {
    fprintf(stderr, "Error: Could not open iNES file for reading\n");
    goto error_cleanup_exit;
  }

  /* Read the header. */
  {
    unsigned char header[HEADER_SIZE];
    size_t bytes_read;

    bytes_read = fread(header,1,HEADER_SIZE,ines_file);
    if( bytes_read != HEADER_SIZE ) {
      fprintf(stderr, "Error: Could not read iNES file header.\n");
      goto error_cleanup_exit;
    }
    if( header[0] != 0x4E
        || header[1] != 0x45
        || header[2] != 0x53
        || header[3] != 0x1A ) {
      fprintf(stderr, "Error: No valid iNES header found.\n");
      goto error_cleanup_exit;
    }
    prg_rom_count = header[4];
    chr_rom_count = header[5];
    /* Bit 3 is 1 if trainer exists, otherwise it is 0. */
    trainer_count = (header[6] & 0x04) >> 2;
  }

  /* Validate the CHR-ROM index. */
  if( chr_rom_index >= chr_rom_count ) {
    fprintf(stderr,
            "Error: CHR-ROM index %d is too large (%d CHR-ROM exist).\n",
            chr_rom_index,
            chr_rom_count);
    goto error_cleanup_exit;
  }

  /* Seek to the CHR-ROM data to extract. */
  {
    int seek_res;
    long int seek_pos;
    size_t bytes_read;
    size_t bytes_written;

    seek_pos = HEADER_SIZE
               + trainer_count*TRAINER_SIZE
               + prg_rom_count*PRG_ROM_SIZE
               + chr_rom_index*CHR_ROM_SIZE;

    seek_res = fseek(ines_file, seek_pos, SEEK_SET);
    if( seek_res != 0 ) {
      fprintf(stderr, "Error: Unable to seek to CHR-ROM position in file.\n");
      goto error_cleanup_exit;
    }
    bytes_read = fread(chr_rom_data,1,CHR_ROM_SIZE,ines_file);
    if( bytes_read != CHR_ROM_SIZE ) {
      fprintf(stderr, "Error: Unable to read CHR-ROM data from iNES file.\n");
      goto error_cleanup_exit;
    }

    bytes_written = fwrite(chr_rom_data,1,CHR_ROM_SIZE,stdout);
    if( bytes_written != CHR_ROM_SIZE ) {
      fprintf(stderr, "Error: Unable to write CHR-ROM data to output.\n");
      goto error_cleanup_exit;
    }
  }
  goto success_cleanup_exit;


success_cleanup_exit:
  assert( ines_file != NULL );
  return 0;

error_cleanup_exit:
  return -1;
}
