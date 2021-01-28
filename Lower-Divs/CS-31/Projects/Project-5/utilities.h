//
//  utilities.hpp
//  flowers
//
//  Created by Charles Zhang on 11/9/19.
//  Copyright © 2019 Charles Zhang. All rights reserved.
//

// utilities.h

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[]);
int randInt(int min, int max);
