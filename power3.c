/* −−−−−−−−−−−−−−−− INCLUSIONS DES BIBLIOTHEQUES NECESSAIRES −−−−−−−−−−−−−−−−−−− */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* −−−−−−−−−−−−−−−− DECLARATIONS DES CONSTANTES PARAMETRIQUES −−−−−−−−−−−−−−−−−− */
#define SCENE_NB_ROW_MAX        (8)
#define SCENE_NB_COL_MAX        (8)
#define SCENE_CELL_VOID_VALUE   ('V')
#define SCENE_CELL_VOID_CHAR    ('-')

#define INPUT_BUFFER_LEN        (64)

#define VERTICAL                (77)                    //This is definitely useless but clarifies what SetDirection() does.
#define HORIZONTAL              (88)
#define DIAGONAL                (99)

/* −−−−−−−−−−−−−−−− PROTOTYPES DES FONCTIONS −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−− */
void SceneDisplay(char pa_sceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol);
void BorderDisplay(int pa_nbCol);
void ColumnDisplay(int pa_nbCol);
void GetMove(int *pa_pISrcRow, int *pa_pISrcCol, int *pa_pIDstRow, int *pa_pIDstCol);
void ConvertDeltaToPositiveInt(int *pa_pIDelta);
int SceneTokenMove(char pa_SceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol, int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol);
int SetIncrement(int *pa_pISrc, int *pa_pIDst);
int SetDirection(int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol);

/* −−−−−−−−−−−−−−−− CORPS DU PROGRAMME : FONCTION MAIN −−−−−−−−−−−−−−−−−−−−−−−−− */
int main(int argc, char *argv[]) {
     
    //const int iSceneNbRow, iSceneNbCol;
    char chScene[SCENE_NB_ROW_MAX][SCENE_NB_COL_MAX] = {
        {'A', 'A', 'V', 'V', 'E', 'B', 'C', 'V'},
        {'V', 'V', 'C', 'D', 'D', 'E', 'D', 'E'},
        {'A', 'E', 'A', 'V', 'E', 'B', 'V', 'A'},
        {'A', 'V', 'C', 'A', 'C', 'V', 'B', 'B'},
        {'V', 'C', 'A', 'C', 'E', 'C', 'B', 'A'},
        {'V', 'D', 'E', 'E', 'D', 'A', 'E', 'A'},
        {'V', 'V', 'B', 'V', 'B', 'V', 'B', 'V'},
        {'V', 'V', 'D', 'D', 'V', 'D', 'B', 'V'}    
    };
    int iSrcRow, iSrcCol, iDstRow, iDstCol;
    int iNbCellsDestroyed;
    
    //Boucle de jeu
   for(int i = 10; i > 0; i--) {

        //Scene initiale / Affichage formate de la scene de jeu
        SceneDisplay(chScene, SCENE_NB_ROW_MAX, SCENE_NB_COL_MAX);

        printf("Il vous reste %d tour(s) pour terminer le jeu.\r\n\r\n", i);

        //Traitement des entrees clavier
        do {
            printf("Enter movement 'srcRow srcCol dstRow dstCol'.\r\n");
            printf("srcRow and dstRow must be included between 0 and %d.\r\nsrcCol and dstCol must be included between 0 and %d.\r\n --> ", SCENE_NB_ROW_MAX - 1, SCENE_NB_COL_MAX - 1);
            GetMove(&iSrcRow, &iSrcCol, &iDstRow, &iDstCol);
        } while(iSrcRow < 0 || iSrcRow > SCENE_NB_ROW_MAX - 1 ||
                iSrcCol < 0 || iSrcCol > SCENE_NB_COL_MAX - 1 ||
                iDstRow < 0 || iDstRow > SCENE_NB_ROW_MAX - 1 ||
                iDstCol < 0 || iDstCol > SCENE_NB_COL_MAX - 1);

        //Algorithme de mouvement des jetons (-> Moteur du jeu)    
        iNbCellsDestroyed = SceneTokenMove(chScene, SCENE_NB_ROW_MAX, SCENE_NB_COL_MAX, iSrcRow, iSrcCol, iDstRow, iDstCol);

    }
    
    return EXIT_SUCCESS;
}

/* −−−−−−−−−−−−−−−− IMPLEMENTATIONS DES FONCTIONS −−−−−−−−−−−−−−−−−−−−−−−−−−−−−− */
void SceneDisplay(char pa_sceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol) {
    
    ColumnDisplay(pa_nbCol);
    BorderDisplay(pa_nbCol);

    for(int i = 0; i < pa_nbRow; i++) {
        printf("%d |", i);
        for(int j = 0; j < pa_nbCol; j++) {
            pa_sceneArray[i][j] == SCENE_CELL_VOID_VALUE
                ? printf("%c", SCENE_CELL_VOID_CHAR)
                : printf("%c", pa_sceneArray[i][j]);
            if(j < pa_nbCol - 1) {
                printf("  ");
            }
        }
        printf("| %d", i);
        printf("\r\n");
    }

    BorderDisplay(pa_nbCol);
    ColumnDisplay(pa_nbCol);

}
void BorderDisplay(int pa_nbCol) {
    
    printf("   ");
        for(int i = 0; i < pa_nbCol; i++) {
        printf("-");
        if(i < pa_nbCol - 1) {
                printf("--");
            }
    }
    printf("\r\n");
}
void ColumnDisplay(int pa_nbCol) {
    
    printf("   ");
    for(int i = 0; i < pa_nbCol; i++) {
        printf("%d  ", i);
    }
    printf("\r\n");
}
void GetMove(int *pa_pISrcRow, int *pa_pISrcCol, int *pa_pIDstRow, int *pa_pIDstCol) {

    char *pToken;
    char buffer[INPUT_BUFFER_LEN];
    const char separators[] = "\r\n ";
    int counter = 0;
    
    *pa_pISrcRow = *pa_pISrcCol = *pa_pIDstRow = *pa_pIDstCol = 0;
    
    printf("Enter movement src -> dst : ");
    fgets(buffer, INPUT_BUFFER_LEN, stdin);
    
    pToken = strtok(buffer, separators);
    if(pToken) {
        *pa_pISrcRow = atoi(pToken);
        pToken = strtok(NULL, separators);
        if(pToken) {
            *pa_pISrcCol = atoi(pToken);
            pToken = strtok(NULL, separators);
            if(pToken) {
                *pa_pIDstRow = atoi(pToken);
                pToken = strtok(NULL, separators);
                if(pToken) {
                    *pa_pIDstCol = atoi(pToken);
                }
            }
        }
    }
}
void ConvertDeltaToPositiveInt(int *pa_pIDelta) {
    
    if(*pa_pIDelta < 0) {
        *pa_pIDelta = -*pa_pIDelta;
    }
}
int SceneTokenMove(char pa_SceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol, int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol) {
    
    int iXIncrement, iYIncrement;
    int iRowToCheck, iColToCheck;
    int iLongestChain[14];
    int iBufferChain[14];
    int iBufferCounter = 0;
    int iLongestCounter = 0;
    int iCombinaisonsIncrements[4][2] = {
        {-1, -1},
        {+1, -1},
        {+0, -1},
        {-1, +0}
    };
    
    // Vérification : Cellule de départ vide OU cellule d'arrivée non vide
    if( pa_SceneArray[pa_srcRow][pa_srcCol] == SCENE_CELL_VOID_VALUE || 
        pa_SceneArray[pa_dstRow][pa_dstCol] != SCENE_CELL_VOID_VALUE) {
        printf("Error : src with '-' value or dst not empty.\r\n");
        return 0;
    }
    
    //Vérification : Axe de déplacement autorisé
    if(!(SetDirection(pa_srcRow, pa_srcCol, pa_dstRow, pa_dstCol))) {
        return 0;
    }
    
    //Vérification : Vacuité des cellules intermédiaires
    iXIncrement = SetIncrement(&pa_srcCol, &pa_dstCol);
    iYIncrement = SetIncrement(&pa_srcRow, &pa_dstRow);
    iRowToCheck = pa_srcRow;
    iColToCheck = pa_srcCol;

    while((iRowToCheck != pa_dstRow) || (iColToCheck != pa_dstCol)) {
        iRowToCheck += iYIncrement;
        iColToCheck += iXIncrement;
        if(pa_SceneArray[iRowToCheck][iColToCheck] != SCENE_CELL_VOID_VALUE) {
            printf("There is a non void cell in the path...\r\n");
        return 0;
        }
    }
    
    // Déplacement du jeton...
    pa_SceneArray[pa_dstRow][pa_dstCol] = pa_SceneArray[pa_srcRow][pa_srcCol];
    pa_SceneArray[pa_srcRow][pa_srcCol] = SCENE_CELL_VOID_VALUE;
    
    //Recherche de la plus longue chaine...
    for(int i = 0; i < 4; i++) {

        //(Ré)initialisation des variables...
        for (int i = 0; i < iBufferCounter; i++) {
            iBufferChain[i] = 0;
        }
        iBufferCounter = 0;
        
        //Définition de l’axe de recherche...
        iXIncrement = iCombinaisonsIncrements[i][0];
        iYIncrement = iCombinaisonsIncrements[i][1];
        
        for(int j = 0; j < 2; j++) {                                                                                                    //Scan dans les 2 sens.
            while(  pa_dstRow + iYIncrement >= 0 && pa_dstRow + iYIncrement < SCENE_NB_ROW_MAX &&                                       //Tant que la case est dans la scène...
                    pa_dstCol + iXIncrement >= 0 && pa_dstCol + iXIncrement < SCENE_NB_COL_MAX &&
                    pa_SceneArray[pa_dstRow + iYIncrement][pa_dstCol + iXIncrement] == pa_SceneArray[pa_dstRow][pa_dstCol]) {           //...et tant qu’elle est de la même "couleur"...
                
                //Ajouter les coordonnées de la case à la chaine buffer.
                iBufferChain[iBufferCounter] = pa_dstRow + iYIncrement;
                iBufferChain[iBufferCounter + 1] = pa_dstCol + iXIncrement;
                iBufferCounter += 2;

                //Incrémenter X et Y pour rechercher plus loin dans l’axe.
                iXIncrement += iCombinaisonsIncrements[i][0];
                iYIncrement += iCombinaisonsIncrements[i][1];
            }
            
            iCombinaisonsIncrements[i][0] = -iCombinaisonsIncrements[i][0];
            iCombinaisonsIncrements[i][1] = -iCombinaisonsIncrements[i][1];
            iXIncrement = iCombinaisonsIncrements[i][0];
            iYIncrement = iCombinaisonsIncrements[i][1];
        }

        //Si c’est la chaine la plus longue à ce jour, la conserver.
        if(iBufferCounter >= iLongestCounter) {
            for(int i = 0; i < iBufferCounter; i++) {
                iLongestChain[i] = iBufferChain[i];
                iLongestCounter = iBufferCounter;
            }
        }
    }
    
    //Destruction des cellules appartenant à la plus longue chaine...
    if(((iLongestCounter / 2) + 1) >= 3) {                                                                  //Si la chaine comporte au moins 3 jetons...
        for(int i = 0; i < iLongestCounter; i += 2) {
            pa_SceneArray[iLongestChain[i]][iLongestChain[i + 1]] = SCENE_CELL_VOID_VALUE;
        }
        pa_SceneArray[pa_dstRow][pa_dstCol] = SCENE_CELL_VOID_VALUE;

        return 1 + (iLongestCounter / 2);
    }
    else {
        printf("This move doesn't create a chain whose length is superior or equal to 3.\r\n");

        pa_SceneArray[pa_srcRow][pa_srcCol] = pa_SceneArray[pa_dstRow][pa_dstCol];                          // Sinon, remise en place du jeton...
        pa_SceneArray[pa_dstRow][pa_dstCol] = SCENE_CELL_VOID_VALUE;
        
        return 0;
    }
}
int SetIncrement(int *pa_pISrc, int *pa_pIDst) {
    
    if(*pa_pISrc < *pa_pIDst) {
        return 1;
    }
    if(*pa_pISrc > *pa_pIDst) {
        return - 1;
    }
    else {
        return 0;
    }
}
int SetDirection(int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol) {
    
    int iDeltaX, iDeltaY;

    iDeltaX = pa_dstCol - pa_srcCol;
    iDeltaY = pa_dstRow - pa_srcRow;
    ConvertDeltaToPositiveInt(&iDeltaX);
    ConvertDeltaToPositiveInt(&iDeltaY);

    if(iDeltaX && !(iDeltaY)) {
        return VERTICAL;
    }
    else if (iDeltaY && !(iDeltaX)) {
        return HORIZONTAL;
    }
    else if(iDeltaX && iDeltaY && (iDeltaX == iDeltaY)) {
        return DIAGONAL;
    }
    else {
        return 0;
    }
}
