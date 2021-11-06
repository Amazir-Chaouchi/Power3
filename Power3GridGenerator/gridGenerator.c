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

int main(int argc, char *argv[]) {
    
    int iGridNbRow, iGridNbCol, iGridNbColours;
    
#ifdef DEBUG
    printf("main() arguments\r\n\targv[1] : %d\r\n\targv[2] = %d\r\n\targv[3] = %d\r\n", *argv[1], *argv[2], *argv[3]);
    printf("nbRow : %d\tnbCol : %d\tnbColours : %d\r\n", iGridNbRow, iGridNbCol, iGridNbColours);
#endif

    // Aucun argument
    if(argc == 1) {
        iGridNbRow = GRID_DEFAULT_NB_ROW;
        iGridNbCol = GRID_DEFAULT_NB_COL;
        iGridNbColours = GRID_DEFAULT_NB_COLOURS;
    }
    
    else if(argc > 1) {
        
        char *ptr_cArgQualif;
        
        // Vérification : Nombre d'arguments
        if(argc != 4) {
            printf("An error occured : ");
            
            (argc < 4)
                ? (ptr_cArgQualif = "few")
                : (ptr_cArgQualif = "many");
                
            printf("Too %s arguments were passed to grid.\r\n", ptr_cArgQualif);
            exit(EXIT_FAILURE);
        }
    
        //Vérification : Validité des arguments
        else {
            
            char *ptr_cErrorMessage;    // N'indique que la première erreur (À FIX)
            int iWrongArg;
            int iMinValue, iMaxValue;
            
            if(*argv[1] < GRID_NB_ROW_MIN) {
                iWrongArg = 1;
                ptr_cArgQualif = "low";
                iMinValue = GRID_NB_ROW_MIN;
                iMaxValue = GRID_NB_ROW_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*argv[1] > GRID_NB_ROW_MAX) {
                iWrongArg = 1;
                ptr_cArgQualif = "high";
                iMinValue = GRID_NB_ROW_MIN;
                iMaxValue = GRID_NB_ROW_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*argv[2] < GRID_NB_COL_MIN) {
                iWrongArg = 2;
                ptr_cArgQualif = "low";
                iMinValue = GRID_NB_COL_MIN;
                iMaxValue = GRID_NB_COL_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*argv[2] > GRID_NB_COL_MAX) {
                iWrongArg = 2;
                ptr_cArgQualif = "high";
                iMinValue = GRID_NB_COL_MIN;
                iMaxValue = GRID_NB_COL_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*argv[3] < GRID_NB_COLOURS_MIN) {
                iWrongArg = 3;
                ptr_cArgQualif = "low";
                iMinValue = GRID_NB_COLOURS_MIN;
                iMaxValue = GRID_NB_COLOURS_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            else if(*argv[3] > GRID_NB_COLOURS_MAX) {
                iWrongArg = 3;
                ptr_cArgQualif = "high";
                iMinValue = GRID_NB_COLOURS_MIN;
                iMaxValue = GRID_NB_COLOURS_MAX;
                
                ptr_cErrorMessage = "%s too %s. Must be included between %d and %d.\r\n";
                printf(ptr_cErrorMessage, argv[iWrongArg], ptr_cArgQualif, iMinValue, iMaxValue);
                exit(EXIT_FAILURE);
            }
            
            //Si toutes les valeurs sont conformes...
            else {
                iGridNbRow = *argv[1];
                iGridNbCol = *argv[2];
                iGridNbColours = *argv[3];
            }
        }
    }
    
    //Définir nbColours en arg de main
    //Définir nombre de col et row en arg de main
    
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
