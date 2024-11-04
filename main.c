#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char* argv[]) {
    Tree root = NULL;
    int t, opt;  
  
    while(1) {
		scanf("%d", &opt);

		switch(opt) {
				int value;
			
				case 1:
						scanf("%d", &value);
						root = insert(root, value, &t);
						break;
				case 2:
                        preOrder(root);
                        printf("\n");
						break;
                case 3:
						scanf("%d", &value);
						root = remov(root, value, &t);
                        break;
				case 99:
						exit(0);
		}
	}
}































































































