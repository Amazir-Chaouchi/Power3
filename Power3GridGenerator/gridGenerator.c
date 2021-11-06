#include <stdio.h>
#include <stdlib.h>

#define DEBUG                       (1)

#define GRID_DEFAULT_NB_ROW         (8)
#define GRID_DEFAULT_NB_COL         (8)
#define GRID_DEFAULT_NB_COLOURS     (5)

#define GRID_NB_ROW_MIN             (5)
#define GRID_NB_ROW_MAX             (20)
#define GRID_NB_COL_MIN             (5)
#define GRID_NB_COL_MAX             (25)
#define GRID_NB_COLOURS_MIN         (3)
#define GRID_NB_COLOURS_MAX         (6)

int CheckArguments(int pa_argc, char *pa_argv[], int *pa_pINbRow, int *pa_pINbCol, int *pa_pINbColours);

int main(int argc, char *argv[]) {
    
    int iGridNbRow, iGridNbCol, iGridNbColours;

    CheckArguments(argc, argv, &iGridNbRow, &iGridNbCol, &iGridNbColours);
    //printf("NbRow : %d\r\nNbCol : %d\r\nNbColours : %d\r\n\r\n", iGridNbRow, iGridNbCol, iGridNbColours);
    
    
    //Générer nbVoidCells aléatoire entre MIN et MAX
    //init nbCellsLeftToGenerate = row * col - nbVoidCells;
    
    //Tant que nbCellsLeftToGenerate > 0
    //  - Créer chaine de char aléa entre 3 et 5
    //      - 80% 3     15% 4       5% 5  #define cette merde
    //      - Def direction aléatoire
    //      - Placer jetons à partir de direction
    
    //Créer fichier de grille
    //Copier tableau dans fichier grille
    
    return EXIT_SUCCESS;
}

int CheckArguments(int pa_argc, char *pa_argv[], int *pa_pINbRow, int *pa_pINbCol, int *pa_pINbColours) {
    
    char *ptr_strArgQualif;
    char *ptr_cErrorMessage;
    char *ptr_strEnd;
    int iWrongArg;
    int iMinValue, iMaxValue;

    // Aucun argument
    if(pa_argc == 1) {
        *pa_pINbRow = GRID_DEFAULT_NB_ROW;
        *pa_pINbCol = GRID_DEFAULT_NB_COL;
        *pa_pINbColours = GRID_DEFAULT_NB_COLOURS;
    }
    
    else if(pa_argc > 1) {
        
        // Vérification : Nombre d'arguments
        if(pa_argc != 4) {
            printf("An error occured : ");
            
            (pa_argc < 4)
                ? (ptr_strArgQualif = "few")
                : (ptr_strArgQualif = "many");
                
            printf("Too %s arguments were passed to grid.\r\n", ptr_strArgQualif);
            exit(EXIT_FAILURE);
        }
    
        else {
            
            //Assignation des valeurs aux variables
            *pa_pINbRow = strtol(pa_argv[1], &ptr_strEnd, 10);
            *pa_pINbCol = strtol(pa_argv[2], &ptr_strEnd, 10);
            *pa_pINbColours = strtol(pa_argv[3], &ptr_strEnd, 10);
            
            //Vérification : Validité des arguments
            if(*pa_pINbRow< GRID_NB_ROW_MIN) {                                                                      // N'indique que la première erreur (À FIX)
                iWrongArg = 1;
                ptr_strArgQualif = "low";
                iMinValue = GRID_NB_ROW_MIN;
                iMaxValue = GRID_NB_ROW_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*pa_pINbRow > GRID_NB_ROW_MAX) {
                iWrongArg = 1;
                ptr_strArgQualif = "high";
                iMinValue = GRID_NB_ROW_MIN;
                iMaxValue = GRID_NB_ROW_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*pa_pINbCol < GRID_NB_COL_MIN) {
                iWrongArg = 2;
                ptr_strArgQualif = "low";
                iMinValue = GRID_NB_COL_MIN;
                iMaxValue = GRID_NB_COL_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*pa_pINbCol > GRID_NB_COL_MAX) {
                iWrongArg = 2;
                ptr_strArgQualif = "high";
                iMinValue = GRID_NB_COL_MIN;
                iMaxValue = GRID_NB_COL_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*pa_pINbColours < GRID_NB_COLOURS_MIN) {
                iWrongArg = 3;
                ptr_strArgQualif = "low";
                iMinValue = GRID_NB_COLOURS_MIN;
                iMaxValue = GRID_NB_COLOURS_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*pa_pINbColours > GRID_NB_COLOURS_MAX) {
                iWrongArg = 3;
                ptr_strArgQualif = "high";
                iMinValue = GRID_NB_COLOURS_MIN;
                iMaxValue = GRID_NB_COLOURS_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, pa_argv[iWrongArg], ptr_strArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
        }
    }
}
