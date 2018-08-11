#include <stdio.h>
#include <stdlib.h>

void expansion ( short int ROld[32], short int RNew[48], short int E[8][6] ){
    int count = 0,i,j;
    for ( i=0 ; i<8; i++ ){
        for ( j=0; j<6; j++ ){
            RNew[count] = ROld[E[i][j]-1];
            count++;
        };
    };
};
void SBox ( short int RNew[48], short int ROld[32] , short int Si[8][4][16] ){
    int i=0, iterate = 0, row, column, element;
    for ( i=0 ; i<8; i++ ){
        iterate = i*6;
        row = RNew[iterate]*2 + RNew[iterate+5]*1;
        column = RNew[iterate+1]*8 + RNew[iterate+2]*4 + RNew[iterate+3]*2 + RNew[iterate+4]*1;
        element = Si[i][row][column];
        iterate = i*4;
        ROld[iterate] = element/8;
        if ( element > 7 )
            element = element - 8;
        ROld[iterate+1] = element/4;
        if ( element > 3 )
            element = element - 4;
        ROld[iterate+2] = element/2;
        if ( element > 1 )
            element = element - 2;
        ROld[iterate+3] = element;
    }
}
void applyP ( short int ROld[32], short int P[8][4] ){
    int count = 0,i,j;
    short int temp[32];
    for ( i=0 ; i<8; i++ ){
        for ( j=0; j<4; j++ ){
            temp[count] = ROld[P[i][j]-1];
            count++;
        };
    };
    for ( i=0 ; i<32; i++ ){
        ROld[i] = temp[i];
    };
};

void convertToInt ( char keyString[65], short int keyArray[64] ){

    int i = 0;
    for ( i=0 ; i<64; i++ ){
        if ( keyString[i] == '0' )
            keyArray[i] = 0;
        else keyArray[i] = 1;
    };

};
void printInputArray ( int row, int column,short int array[row][column] ){
    int i=0, j=0;
    for ( i=0 ; i< row; i++ ){
        printf("|");
        for ( j=0; j<column; j++ ){
            printf(" %2hd |", array[i][j]);
        };
        printf("\n");
    };
};
void updateKeyArray( short int keyArray[64],short int PC1[8][7], short int permutatedKeyArray[56] ){
    int count = 0,i,j;
    for ( i=0 ; i<8; i++ ){
        for ( j=0; j<7; j++ ){
            permutatedKeyArray[count] = keyArray[PC1[i][j]-1];
            count++;
        };
    };
}
void updateMessageArray( short int messageArray[64],short int IP[8][8]){
    int count = 0,i,j;
    short int temp[64];
    for ( i=0 ; i<8; i++ ){
        for ( j=0; j<8; j++ ){
            temp[count] = messageArray[IP[i][j]-1];
            count++;
        };
    };
    for ( i=0 ; i<64; i++ ){
        messageArray[i] = temp[i];
    };
};
void getRoundKeys( short int roundKeys[16][48], short int permutatedKeyArray[56], short int PC2[8][6] ){
    int i,j,k,count=0,shift;
    short int temp[56];
    short int L1[28],R1[28],tempL1[28],tempR1[28];
    for ( i=0; i<28; i++ ){
        L1[i] = permutatedKeyArray[i];
        R1[i] = permutatedKeyArray[i+28];
    };
    for ( i=0 ; i<16; i++ ){
        count = 0;
        shift = i + 1;
        for ( j=0 ; j<28; j++ ){
            temp[j] = L1[j];
            temp[28+j] = R1[j];
        };
        for ( k=0 ; k<8; k++ ){
            for ( j=0; j<6; j++ ){
                roundKeys[i][count] = temp[PC2[k][j]-1];
                count++;
            };
        };
        for ( j=0 ; j<28 ; j++ ){
            if ( j>= shift ){
                tempL1[j-shift] = L1[j];
                tempR1[j-shift] = R1[j];
            }else {
                tempL1[28 - shift + j] = L1[j];
                tempR1[28 - shift + j] = R1[j];
            }
        }
        for ( j=0 ; j<28; j++ ){
            L1[j] = tempL1[j];
            R1[j] = tempR1[j];
        }
    }
}
void getEncryptedMessage ( short int messageArray[64], short int roundKeys[16][48] , short int E[8][6] , short int S[8][4][16], short int P[8][4] ){
    short int temp[64],i,j;
    short int LNew[32],RNew[48],LOld[32],ROld[32];
    for ( i=0 ; i<16; i++ ){
        for ( j=0 ; j<32; j++ ){
            LOld[j] = messageArray[j];
            ROld[j] = messageArray[32+j];
            LNew[j] = messageArray[32+j];
        };
        expansion( ROld, RNew, E );
        for ( j=0 ; j<48; j++ ){
            RNew[j] = RNew[j]^roundKeys[i][j];
        };
        SBox ( RNew, ROld, S );
        applyP ( ROld, P );
        for ( j=0 ; j<32; j++ ){
            ROld[j] = ROld[j]^LOld[j];
        };
        for ( j=0 ; j<32; j++ ){
          messageArray[j] = LNew[j];
          messageArray[32+j] = ROld[j];
        };
    };
    for ( j=0 ; j<64; j++ ){
        messageArray[j] = ROld[j];
        messageArray[32+j] = LNew[j];
    };

}

int main()
{
    int i=0,j=0,k=0;
    short int keyArray[64], permutatedKeyArray[56],messageArray[64];
    short int PC1[8][7],PC2[8][6],IP[8][8],E[8][6],P[8][4],IP2[8][8];
    short int S[8][4][16];
    short int roundKeys[16][48];
    char keyString[65],message[65];
    printf("Give the key K: \n");
    scanf("%s",keyString);
    convertToInt( keyString, keyArray );
    printf("Give the message M: \n");
    scanf("%s",message);
    convertToInt( message, messageArray );
    printf("Give the Permutation PC1: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<7; j++ ){
            scanf("%hd",&PC1[i][j]);
        };
    };
    printf("Give the Permutation PC2: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<6; j++ ){
            scanf("%hd",&PC2[i][j]);
        };
    };
    printf("Give the Permutation IP: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<8; j++ ){
            scanf("%hd",&IP[i][j]);
        };
    };
    printf("Give the Permutation IP2: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<8; j++ ){
            scanf("%hd",&IP2[i][j]);
        };
    };
    printf("Give the Expansion table E: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<6; j++ ){
            scanf("%hd",&E[i][j]);
        };
    };
    printf("Give the Permutation P: \n");
    for ( i=0 ; i<8 ; i++ ){
        for ( j=0; j<4; j++ ){
            scanf("%hd",&P[i][j]);
        };
    };
    for ( k=0 ; k<8; k++ ){
       printf("Give the S-box table S%d: \n",k+1);
        for ( i=0 ; i<4 ; i++ ){
            for ( j=0; j<16; j++ ){
                scanf("%hd",&S[k][i][j]);
            };
        };
    };
    updateKeyArray(keyArray,PC1,permutatedKeyArray);
    updateMessageArray(messageArray,IP);
    getRoundKeys(roundKeys, permutatedKeyArray, PC2 );
    getEncryptedMessage(messageArray,roundKeys,E,S,P);
    updateMessageArray(messageArray,IP2);
    printf("Cipher Text:\n");
    for ( i=0 ; i<64; i++ ){
        printf("%hd",messageArray[i]);
    }

    return 0;
}
