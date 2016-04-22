#include "stdio.h"
#include "string.h"
#define N 5000
#define r 256// ASCII
#define R 26 //�������� �������� �����

int main()
{
	FILE* fp1;
	fp1 = fopen("input.txt", "r");
	char matched[N][50]; //������ � ���������� ����������
	int max_match_sum = 0; //���-�� ���������� ����������
	int max_match_ind;// ������ ������������� ���������� ���-��
	int s;
	int i = 0, j, l, g, z,k=0; //��������
	char S[N]; //������ � ������//����� ������

	while((S[k]=fgetc(fp1))&&(S[k]!=EOF))
		k++;
	
	char alf[R] = { 'a','b','c','d','e','f','h','i','j','k','l','m','n','o','p','r','s','t','u','w','v','q','z','g' ,'x' };//����� ����������� ��������

	int lenght_distance[N][2] = { 0 };//� lenght_distane[][0] ��������� ����� ����������, � lenght_distance[][1] ���������� ����� ������������
	int w = 0; // ����� ����������
	int max_lenght_matched = 0; //������������ ���������� �� �����
	int max_m = -1; //������; ������������� ����������
	for (i = 0; i < R; i++)//i-����������� �� ���� �������� ��������
	{
		for (j = 0; j < k; j++) // ���� ��� ������� Alf[i] � S[]
			if (S[j] == alf[i])
				for (l = j+1; l < k; l++)// l - ���� ��� ������� Alf[i] � ������ S[j+]
				{
					if (S[l] == alf[i])
					{
						g = 0;
						while (((l + g) < k) && ((j + g) < k) && (S[l + g] == S[j + g]))
							g++;                                                          //g ������� ������� �������� �������
						if (g > 2)
						{
							for (z = 0; z < g; z++)
								matched[w][z] = S[l + z];
							
							matched[w][z] = '\0';
							lenght_distance[w][0] = g;
							lenght_distance[w][1] = l - j; // ���������� ����� ������������
							w++;
						}


					}
				}
	}
	char buff[50];
	for (j = 0; j < w-1; j++) 
	{
		max_lenght_matched = 0;
		for (i = j; i < w; i++)
			if (lenght_distance[i][0]>max_lenght_matched)
			{
				max_lenght_matched = lenght_distance[i][0];      // �������� ����� ������������ ���������� � ��������� ����� ����( c������ ��� 100%)
				max_m = i;
			}
		max_lenght_matched = lenght_distance[j][0];
		lenght_distance[j][0] = lenght_distance[max_m][0];    //��������� ���������� �� �����, ������� ������ ����� � ��������� �������.
		lenght_distance[max_m][0] = max_lenght_matched;
		max_lenght_matched = lenght_distance[j][1];
		lenght_distance[j][1] = lenght_distance[max_m][1];
		lenght_distance[max_m][1] = max_lenght_matched;
		strcpy(buff, matched[j]);
		strcpy(matched[j], matched[max_m]);
		strcpy(matched[max_m], buff);

	}
	
	for (i = 0; i < w - 1; i++)
	{
		s = 0;
		
		for (j = i; j < w; j++)
		{

			z = 0;
			while (matched[i][z] && matched[j][z] && (matched[i][z] == matched[j][z]))
			{
				z++;
			}
			if ((matched[i][z] == '\0') && (matched[j][z] == '\0'))
				s++;


		}
		if ((max_match_sum < s))
		{
			max_match_sum = s;
			max_match_ind = i;
		}
	}
	for (i = 0; i < w; i++)
	{
		printf("%s ", matched[i]);
	}
	float h;
	for (j =1 ; j < 100; j++)
	{
		 h = 0;
		for (i = 0; i < w; i++)
		{
			if ((lenght_distance[i][1] % j) == 0)
				h++;
		}
		
		h /= w;
		printf("%d %f \%",j,h*100);

	}
	printf("%d %s", max_match_sum, matched[max_match_ind]);


	return 0;


}