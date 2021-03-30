#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // 행렬 생성 함수
void print_matrix(int** matrix, int row, int col); // 행렬 출력하는 함수
int free_matrix(int** matrix, int row, int col); // 행렬 초기화 함수
int fill_data(int** matrix, int row, int col); // 행렬 값 대입 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬의 합 구하기 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬의 차 구하기 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 전치 행렬 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬 곱 함수

int main()
{

	char command; // 문자형 변수 command 생성
	printf("[----- [민선홍]  [2018038028] -----]\n");

	int row, col;
	srand(time(NULL)); // 초당 무작위로 반환

	printf("Input row and col : ");
	fflush(stdout); // 버퍼비우기
	scanf("%d %d", &row, &col);
	int** matrix_a = create_matrix(row, col); //create_matrix 함수에 할당 받아 이중포인터 matrix_a에 대입
	int** matrix_b = create_matrix(row, col); //create_matrix 함수에 할당 받아 이중포인터 matrix_b에 대입
	int** matrix_a_t = create_matrix(col, row);  //create_matrix 함수에 할당 받아 이중포인터 matrix_a_t에 대입

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; } // 만약 행렬_a or 행렬_b 가 null 값이면 -1 반환(비정상 종료)

	do { // matrix maniupulation 창을 띄우는 반복문
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout); // 버퍼 비우기
		scanf(" %c", &command); // command 값 입력

		switch (command) { // command의 값에 따라 출력하는 조건문
		case 'z': case 'Z': // command의 값이 z or Z 이면
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); // matrix_a 행렬의 값 대입 함수 불러오기
			fill_data(matrix_b, row, col); // matrix_b 행렬의 값 대입 함수 불러오기
			break;
		case 'p': case 'P': // command의 값이 p or P 이면
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // matrix_a 행렬의 값 출력
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // matrix_b 행렬의 값 출력
			break;
		case 'a': case 'A': // command의 값이 a or A 이면
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // matrix_a 와 matirx_b 의 합 구하기 함수 불러오기
			break;
		case 's': case 'S': // command의 값이 s or S 이면
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a 와 matrix_b의 차 구하기 함수 불러오기
			break;
		case 't': case 'T': // command의 값이 t or T 이면
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // matrix_a의 전치 행렬 구하기 함수 불러오기
			print_matrix(matrix_a_t, col, row); // matrix_a의 전치함수인 matirx_a_t 행렬 출력
			break;
		case 'm': case 'M': // command의 값이 m or M 이면
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // matrix_a의 전치 행렬 구하기 함수 불러오기
			multiply_matrix(matrix_a, matrix_a_t, row, col); // matrix_a 와 그에 따른 전치 행렬 곱 함수 불러오기
			break;
		case 'q': case 'Q': // command의 값이 q or Q이면
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row); // matirx_a_t 값 초기화
			free_matrix(matrix_a, row, col); // matrix_a 값 초기화
			free_matrix(matrix_b, row, col); // matrix_b 값 초기화
			break;
		default: // 그 외에는 concentration!! 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); // q or Q 아니라면, 반복실행

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	int** result; // 이중포인터 정수형 변수 result 생성
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	if (row <= 0 || col <= 0) { // row의 값과 col의 값이 0이거나 작으면 NULL 반환 (비정상 종료)
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	result = (int**)malloc(row * sizeof(int*)); // 동적할당을 이용한 행렬 생성
	for (i = 0; i < row; i++) // row 전까지 반복문 실행
	{
		result[i] = (int*)malloc(col * sizeof(int)); // 동적할당을 이용한 행렬 생성
		for (j = 0; j < col; j++) {
			result[i][j] = -1;
		}
	}

	return result;
}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // 행렬 출력하는 함수
{
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	for (i = 0; i < row; i++) // 이중for문을 이용하여 행렬 출력
	{
		for (j = 0; j < col; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}
}

/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // 행렬 초기화하는 함수
{
	if (matrix == NULL) { // 행렬의 값이 NULL이 있으면 -1 반환하는 조건문(비정상종료)
		printf("Matrix is NULL\n");
		return -1;
	}
	for (int i = 0; i < row; i++) // matrix의 값을 초기화하기 위해 사용하는 반복문
	{
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // 행렬 값을 대입하는 함수
{
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	if (matrix == NULL) { // 행렬의 값이 NULL이 있으면 -1 반환하는 조건문 (비정상종료)
		printf("Matrix is NULL\n");
		return -1;
	}

	for (i = 0; i < row; i++) // 이중 for 문을 이용하여 행과열에 랜덤으로 0~19까지 대입하는 반복문
	{
		for (j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 20;
		}
	}
	return 0;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬 a와 행렬 b의 합을 구하는 함수
{
	int** matrix_add = create_matrix(row, col); // 이중포인터 정수형 변수 matrix_add를 create_matrix 함수에서 불러와 생성
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	if (matrix_a == NULL || matrix_b == NULL ) { // 행렬 a의 값과 행렬 b의 값이 NULL 이면 -2 반환 (비정상종료)
		printf("Matrix is NULL\n");
		return -2;
	}

	for (i = 0; i < row; i++) // 이중 for문을 이용해서 행렬 a와 행렬 b의 행과 열을 찾아 합을 구하는 반복문
	{
		for (j = 0; j < col; j++)
		{
			matrix_add[i][j] = matrix_a[i][j] + matrix_b[i][j];
		}
	}
	if (matrix_add == NULL) // matrix_add의 값이 NULL이면 -3 반환(비정상 종료)
	{
		printf("Matrix_add is NULL\n");
		return -3;
	}

	print_matrix(matrix_add, row, col); // matrix_add의 값 출력하기 위해 print_matrix함수에 값 대임
	free_matrix(matrix_add, row, col); // matrix_add의 값 초기화
	return 0;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a와 matrix_b의 차를 구하는 함수
{
	int** matrix_sub = create_matrix(row, col); // 이중포인터 정수형 변수 matrix_sub를 create_matrix 함수에서 불러와 생성
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	if (matrix_a == NULL || matrix_b == NULL) { // matrix_a 와 matrix_b 의 값이 NULL 이면 -2 반환 (비정상 종료)
		printf("Matrix is NULL\n");
		return -2;
	}

	for (i = 0; i < row; i++) // 이중 for문을 이용해서 행렬 a와 행렬 b의 행과 열을 찾아 차를 구하는 반복문
	{
		for (j = 0; j < col; j++)
		{
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
		}
	}
	if (matrix_sub == NULL) // matrix_sub의 값이 NULL이면 -3 반환(비정상 종료)
		{
			printf("Matrix_sub is NULL\n");
			return -3;
		}
	print_matrix(matrix_sub, row, col); // matrix_sub 값 출력하기 위해 print_matrix함수에 값 대임
	free_matrix(matrix_sub, row, col); // matrix_sub 값 초기화
	return 0;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // matrix_a의 전치행렬을 구하는 함수
{
	int i; // 정수형 변수 i 생성
	int j; // 정수형 변수 j 생성

	if (matrix == NULL) { // matrix_a의 값이 NULL이면 -1 반환 (비정상 종료)
		printf("Matrix is NULL\n");
		return -1;
	}


	for (i = 0; i < row; i++) // 이중 for문을 이용하여 matrix_a의 전치행렬 구하는 반복문
	{
		for (j = 0; j < col; j++)
		{
			matrix_t[i][j] = matrix[j][i]; // 전치행렬이기 때문에 [i][j]와 [j][i]를 사용
		}
	}
	if (matrix_t == NULL) // matrix_t의 값이 NULL이면 -3 반환(비정상 종료)
		{
			printf("Matrix_t is NULL\n");
			return -3;
		}
	return 0;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // matrix_a와 그에 대한 전치행렬에 곱을 구하는 함수
{
	int i, j, k; // 정수형 변수 i j k 생성
	int tmp; // 정수형 변수 tmp 생성
	int** matrix_mul = NULL; // 이중포인터 정수형 변수 amtrix_mul에 NULL 값 대입

	if (matrix_a == NULL || matrix_t == NULL) { //matrix_a의 값이 NULL이거나 matrix_t의 값이 NULL이면 -3 반환
		printf("Matrix is NULL\n");
		return -3;
	}

	matrix_mul = create_matrix(row, row); // create_matrix를 이용하여 matrix_mul 행과 열 생성 (곱이기 때문에 row row 사용)

	for (i = 0; i < row; i++) { //3중 for문을 이용하여 행렬의 곱을 구하는 반복문
		for (j = 0; j < row; j++) {
			tmp = 0; // 연산하기 위해 tmp는 0으로 초기화
			for (k = 0; k < col; k++) {
				tmp += matrix_a[i][k] * matrix_t[k][j]; // a행렬의 i행의 값들과 전치행렬의 j열의 값들을 곱한 후에 더한다
			}
			matrix_mul[i][j] = tmp; // 더한 값을 matrix_mul에 저장한다
		}
	}
	if (matrix_mul == NULL) // matrix_mul의 값이 NULL이면 -3 반환(비정상 종료)
		{
			printf("Matrix_mul is NULL\n");
			return -3;
		}
	print_matrix(matrix_mul, row, row); // print_matrix 함수를 이용하여 matrix_mul 출력
	free_matrix(matrix_mul, row, row); // matrix_mul 값 초기화

	return 0;
}
