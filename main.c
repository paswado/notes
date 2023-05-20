#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTES_FILE "notes.txt"
#define MAX_NOTES 128
#define MAX_NOTE_LENGTH 1024


struct Note {
    int index;
    char *note;
};

typedef struct Note Note;

void print_notes() {
    FILE *fp = fopen(NOTES_FILE, "r");
    char chunk[MAX_NOTE_LENGTH];
    int i = 1;

    if(fp == NULL) {
        perror("Failed to open file\n");
        exit(1);
    }

    while(fgets(chunk, sizeof(chunk), fp) != NULL){
        printf("%d. ", i++);
        fputs(chunk, stdout);
    }

    fclose(fp);
}

void print_notes_2(Note *notes, const int note_count){
    for ( int i = 0; i < note_count; i++){
        printf("%d. %s\n", notes[i].index, notes[i].note);
    }

}

void delete_note(int note_index) {
    FILE *fp = fopen(NOTES_FILE, "r");

    if (fp == NULL) {
        perror("Failed to open notes file");
        exit(1);
    }

    Note* notes = (Note *)malloc(MAX_NOTES * sizeof(Note));
    char chunk[MAX_NOTE_LENGTH];
    int i = 0;
    int notes_count;

    while(fgets(chunk, sizeof(chunk), fp) != NULL){
        notes[i].index = i;
        notes[i].note = (char *)malloc(sizeof(char) * strlen(chunk));
        strcat(notes[i].note, chunk);
        i++;
    }

    fclose(fp);

    notes_count = i;

    for ( i = 0; i < notes_count; i++){
        printf("%s", notes[i].note);
        free(notes[i].note);
    }

    free(notes);
}

int read_notes(const char *filename, Note **notes) {
    FILE *fp = fopen(NOTES_FILE, "r");

    // Note* notes;
    int i = 0;
    int notes_count;

    if (fp == NULL) {
        perror("Failed to open notes file");
        exit(1);
    }

    *notes = (Note *)malloc(MAX_NOTES * sizeof(Note));

    char *buff = (char *)malloc(sizeof(char) * MAX_NOTE_LENGTH);
    while(fgets(buff, sizeof(buff), fp) != NULL){
        (*notes)[i].index = i;
        (*notes)[i].note = (char *)malloc(sizeof(char) * strlen(buff));
        strcat((*notes)[i].note, buff);
        i++;
    }
    free(buff);

    fclose(fp);
    return i;
}


void write_notes(const char *filename, Note *note) {
    printf("Not implemented");
}


int delete_note_2(int index, Note **notes, int notes_length){
    free((*notes)[index].note);

    for(int i = index; i < notes_length; i++){
        if (i < notes_length - 1) {
            (*notes)[i].note = (*notes)[i + 1].note;
        }else{
            (*notes)[i].note = NULL;
        }
    }

    return notes_length - 1;
}

int main(int argc, char *argv[]) {
    Note *notes;
    int note_count = 0;

    if ( argc < 2) {
        note_count = read_notes(NOTES_FILE, &notes);
        print_notes_2(notes, note_count);
        exit(0);
    }

    if (!strcmp(argv[1], "-a")) {
        printf("Add command issued\n");
    }

    if (!strcmp(argv[1], "-d") && argc >= 3) {
        char *end;
        const long note_number = strtol(argv[2], &end, 10);

        printf("Delete note #%d\n", (int)note_number);
        note_count = delete_note_2((int)note_number, &notes, note_count);
        print_notes_2(notes, note_count);
    }

    exit(0);
}
