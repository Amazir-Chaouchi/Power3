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
int SceneTokenMove(char pa_SceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol, int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol);
int SceneInit(char pa_sceneArray[][SCENE_NB_COL_MAX], int *pa_pINbRow, int *pa_pINbCol, char pa_fileNameStr[]);
int SetIncrement(int *pa_pISrc, int *pa_pIDst);
int SetDirection(int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol);

/* −−−−−−−−−−−−−−−− CORPS DU PROGRAMME : FONCTION MAIN −−−−−−−−−−−−−−−−−−−−−−−−− */
int main(int argc, char *argv[]) {
     
    char chScene[SCENE_NB_ROW_MAX][SCENE_NB_COL_MAX];
    char *cFileName;
    int iSrcRow, iSrcCol, iDstRow, iDstCol;
    int iNbCellsDestroyed;
    int iSceneNbRow, iSceneNbCol;
    int iNbTours, iNbVoidCells;
    
    //Passage de la grille (fichier externe) en paramètre de main
    if(argc > 1) {
        cFileName = argv[1];
    }
    else {
        cFileName = "default.txt";
    }
    
    //Initialisation de la grille
    iSceneNbRow = iSceneNbCol = 0;
    iNbVoidCells = SceneInit(chScene, &iSceneNbRow, &iSceneNbCol, cFileName);
    
    //Scene initiale
    SceneDisplay(chScene, iSceneNbRow, iSceneNbCol);
    
    printf("Enter movement 'srcRow srcCol dstRow dstCol'.\r\n\r\n");
    printf("\tsrcRow and dstRow must be included between 0 and %d.\r\n\tsrcCol and dstCol must be included between 0 and %d.\r\n\r\n", iSceneNbRow - 1, iSceneNbCol - 1);
    
    //Boucle de jeu
    iNbCellsDestroyed = 0;
    iNbTours = 0;
    
    do {

        //Traitement des entrees clavier
        do {
            GetMove(&iSrcRow, &iSrcCol, &iDstRow, &iDstCol);
        } while(iSrcRow < 0 || iSrcRow > SCENE_NB_ROW_MAX - 1 ||
                iSrcCol < 0 || iSrcCol > SCENE_NB_COL_MAX - 1 ||
                iDstRow < 0 || iDstRow > SCENE_NB_ROW_MAX - 1 ||
                iDstCol < 0 || iDstCol > SCENE_NB_COL_MAX - 1);
        printf("\r\n");

        //Algorithme de mouvement des jetons (-> Moteur du jeu)    
        iNbCellsDestroyed += SceneTokenMove(chScene, SCENE_NB_ROW_MAX, SCENE_NB_COL_MAX, iSrcRow, iSrcCol, iDstRow, iDstCol);
        iNbTours++;
        
        //Affichage formate de la scene de jeu
        SceneDisplay(chScene, iSceneNbRow, iSceneNbCol);
        
        //Si condition de victoire validée, affichage de la scène vide + message de victoire.
        if(iNbCellsDestroyed == (iSceneNbRow * iSceneNbCol - iNbVoidCells)) {
            printf("\t\tFÉLICITATIONS !!! VOUS AVEZ GAGNÉ !\r\n");
            printf("\t\tGrille résolue en %d tour(s).\r\n", iNbTours);
            return EXIT_SUCCESS;
        }
        
    } while(iNbCellsDestroyed <= (iSceneNbRow * iSceneNbCol - iNbVoidCells));
}

/* −−−−−−−−−−−−−−−− IMPLEMENTATIONS DES FONCTIONS −−−−−−−−−−−−−−−−−−−−−−−−−−−−−− */
int SceneInit(char pa_sceneArray[][SCENE_NB_COL_MAX], int *pa_pINbRow, int *pa_pINbCol, char pa_fileNameStr[]) {
    FILE *ptr_fSceneGrid;
    char c;
    int iCurrentRow, iCurrentCol;
    int iNbPassedChar;
    int iNbChar, iNbVoid;
    
    //Calcul du nombre de ligne et de colonnes.
    iNbChar = iNbVoid = 0;
    
    ptr_fSceneGrid = fopen(pa_fileNameStr, "r");
    if(ptr_fSceneGrid == NULL) {
        perror("Erreur à l'ouverture du fichier\r\n");
    }
    else {
        while((c = fgetc(ptr_fSceneGrid)) != EOF) {
            if((c >= 'A' && c <= 'E') || (c == 'V')) {
                if(c == 'V') {
                    iNbVoid++;
                }
                iNbChar++;
            }
            else if(c == '\n') {
                *pa_pINbRow += 1;
            }
        }
        *pa_pINbCol = iNbChar / *pa_pINbRow;
        fclose(ptr_fSceneGrid);
    }
        
    //Copie du fichier dans iScene.
    iCurrentRow = iCurrentCol = 0;
    iNbPassedChar = 0;
    
    ptr_fSceneGrid = fopen(pa_fileNameStr, "r");
    if(ptr_fSceneGrid == NULL) {
        perror("Erreur à l'ouverture du fichier\r\n");
    }
    else {
        do {            
            do {
                c = fgetc(ptr_fSceneGrid);
                if((c >= 'A' && c <= 'E') || c == 'V') {
                    pa_sceneArray[iCurrentRow][iCurrentCol] = c;
                    iNbPassedChar++;
                    iCurrentCol++;
                }
            } while(iCurrentCol < *pa_pINbCol);
            
            iCurrentCol = 0;
            iCurrentRow++;
        } while(iNbPassedChar < (*pa_pINbRow * *pa_pINbCol));
        fclose(ptr_fSceneGrid);
    }
    
    return iNbVoid;
}
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
    
    printf("\r\n");
    
    //Séparateur entre les tours.
    for(int i = 0; i < 80; i++) {
        printf("-");
    }
    printf("\r\n");

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
    
    *pa_pISrcRow = *pa_pISrcCol = *pa_pIDstRow = *pa_pIDstCol = 0;
    
    printf("Enter movement or press Q to quit : ");
    fgets(buffer, INPUT_BUFFER_LEN, stdin);
    
    pToken = strtok(buffer, separators);
    if(pToken[0] == 'Q' || pToken[0] == 'q') {                                       // Si l'utilisateur appuie sur Q pour quitter...
        exit(EXIT_SUCCESS);                                                         // Sortir du programme.
    }
    
    else {
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
}
int SceneTokenMove(char pa_SceneArray[][SCENE_NB_COL_MAX], int pa_nbRow, int pa_nbCol, int pa_srcRow, int pa_srcCol, int pa_dstRow, int pa_dstCol) {
    
    int iXIncrement, iYIncrement;
    int iRowToCheck, iColToCheck;
    int iBufferCounter, iLongestCounter;
    int iBufferChain[7][2], iLongestChain[7][2];
    int iCombinaisonsIncrements[4][2] = {
        {-1, -1},
        {+1, -1},
        {+0, -1},
        {-1, +0}
    };
    
    // Vérification : Cellule de départ vide OU cellule d'arrivée non vide
    if( pa_SceneArray[pa_srcRow][pa_srcCol] == SCENE_CELL_VOID_VALUE || 
        pa_SceneArray[pa_dstRow][pa_dstCol] != SCENE_CELL_VOID_VALUE) {
        printf("\tERROR : src with '-' value or dst not empty.\r\n\r\n");
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
            printf("\tERROR : There is a non void cell in the path...\r\n\r\n");
        return 0;
        }
    }
    
    //Vérification : Obtention d'une chaine d'au moins 3 jetons
    
    // Déplacement virtuel du jeton pour vérification
    pa_SceneArray[pa_dstRow][pa_dstCol] = pa_SceneArray[pa_srcRow][pa_srcCol];
    pa_SceneArray[pa_srcRow][pa_srcCol] = SCENE_CELL_VOID_VALUE;
    
    //Recherche de la plus longue chaine...
    
    //Initialisation des longueurs des chaînes à 0...
    iBufferCounter = iLongestCounter = 0;
    
    for(int i = 0; i < 4; i++) {

        //(Ré)initialisation des variables...
        for (int i = 0; i < iBufferCounter; i++) {
            iBufferChain[i][0] = iBufferChain[i][1] = 0;
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
                iBufferChain[iBufferCounter][0] = pa_dstRow + iYIncrement;
                iBufferChain[iBufferCounter][1] = pa_dstCol + iXIncrement;
                iBufferCounter++;

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
                iLongestChain[i][0] = iBufferChain[i][0];
                iLongestChain[i][1] = iBufferChain[i][1];
                iLongestCounter = iBufferCounter;
            }
        }
    }
    
    //Destruction des cellules appartenant à la plus longue chaine...
    if((iLongestCounter + 1) >= 3) {                                                                        //Si la chaine comporte au moins 3 jetons...
        for(int i = 0; i < iLongestCounter; i++) {
            pa_SceneArray[iLongestChain[i][0]][iLongestChain[i][1]] = SCENE_CELL_VOID_VALUE;
        }
        pa_SceneArray[pa_dstRow][pa_dstCol] = SCENE_CELL_VOID_VALUE;

        return (iLongestCounter + 1);
    }
    else {
        printf("ERROR : This move doesn't create a chain whose length is superior or equal to 3.\r\n");

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

    iDeltaX = abs(pa_dstCol - pa_srcCol);
    iDeltaY = abs(pa_dstRow - pa_srcRow);

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
