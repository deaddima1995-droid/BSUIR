#include "Task_1_1.h"
#include <stdio.h>
#include <math.h>

/*	��������� ��������� ��� ������� ���� �������� z1 � z2, ���������� ������� ������ ���������. 
	�������� �������� ������ ������� � ����������, pi = 3.1415926 , a � b - � �������� 
	z1 = ; z2 = -sqrt(a)	
*/

const double pi =  3.1415926;

void main(void) {

	double z1, z2;
	double angleRadian = 4;
	double angleGrade = 180 / pi * angleRadian;

	z1 = (sqrt(pow(3 * angleGrade + 2,2) - 24 * angleGrade)) / (3 * sqrt(angleGrade) - 2 / sqrt(angleGrade));
	z2 = -sqrt(angleGrade);

	printf("Answer:\n\tz1 = %f\n\tz2 = %f", z1, z2);
}