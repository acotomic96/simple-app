#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>


static const int_least32_t treshold1 = 20;
static const int_least32_t treshold2 = 30;
static const int_least32_t treshold3 = 40;


typedef struct _s
{
	int_least32_t value;
	int_least16_t index;
} val_ind_struct_t;

static val_ind_struct_t struct_array[4000];
//= {41, 55, 27, 33, 33, 33, 27, 79, 15, 50};


static void bubble_sort(val_ind_struct_t* str_array, int_least16_t n)
{
	int_least16_t i;
	int_least16_t j;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (str_array[i].value < str_array[j].value)
			{
				val_ind_struct_t tmp;
				
				tmp = str_array[i];
				str_array[i] = str_array[j];
				str_array[j] = tmp;
			}
		}
	}
}
int_least32_t compare(const void* x, const void* y)
{
    int_least32_t xx, yy;
    xx = ((val_ind_struct_t *)x)->value;
    yy = ((val_ind_struct_t *)y)->value;
    return yy - xx;
}

static void quick_sort(val_ind_struct_t* str_array, int_least16_t n)
{
	qsort(str_array, n, sizeof(str_array[0]), compare);
}


static void print(const val_ind_struct_t* str_array, int_least16_t n, int_fast8_t tr_index)
{
	int_least16_t i = 0;
	int_least32_t treshold;
	printf("Up to the %"PRIdFAST8". treshold: ", tr_index);

	if(tr_index == 1)
	treshold = treshold1;
	else if(tr_index == 2)
	treshold = treshold2;
	else if(tr_index == 3)
	treshold = treshold3;

	while (str_array[i].value > treshold && i < n)
	{
		printf("%"PRIdLEAST32"(%"PRIdLEAST16") ", str_array[i].value, str_array[i].index);
		i++;
	}
	printf("\n");
}

void main()
{
	int_least16_t i;
	int_least16_t n;
	int_fast8_t treshold_index;
	int_fast8_t sort_index;
	printf("Number of elements: ");
	scanf("%"SCNdLEAST16, &n);
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%"PRIdLEAST16". element: ", i);
		scanf("%"SCNdLEAST32, &(struct_array[i].value));
		struct_array[i].index = i;
		printf("\n");
	}
	do
	{
	printf("Trashold you want to use (1, 2, or 3): ");
	scanf("%"SCNdFAST8, &treshold_index);
	printf("\n");
	}while(treshold_index < 1 || treshold_index > 3);
	
	do
    {
	printf("Sorting algorithm you want to use (1- bubble, 2- quick): ");
	scanf("%"SCNdFAST8, &sort_index);
	printf("\n");
    }while(sort_index < 1 || sort_index > 3);
    
    void (*sortptr[2])(val_ind_struct_t *, int_least16_t) = { bubble_sort, quick_sort}; 
    
	if(sort_index == 1)
		sortptr[0](struct_array, n);
	else 
	if(sort_index == 2)
		sortptr[1](struct_array, n);
		
	print(struct_array, n, treshold_index);
}
