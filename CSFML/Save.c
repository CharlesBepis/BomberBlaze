#include "Save.h"

void ReadHiscore(int* _score)
{
	FILE* Save;
	if (fopen_s(&Save, "Data/Hiscore.txt", "r") != 0)
	{
		return EXIT_FAILURE;
	}
	if (Save)
	{
		fscanf_s(Save, "%d", _score);

		fclose(Save);
	}
}

int GetHiscore()
{
	int hiscore = 0;
	FILE* Save;
	if (fopen_s(&Save, "Data/Hiscore.txt", "r") != 0)
	{
		return EXIT_FAILURE;
	}
	if (Save)
	{
		fscanf_s(Save, "%d", &hiscore);

		fclose(Save);
	}

	return hiscore;
}

void SaveHiscore(int _score)
{
	FILE* Save;
	if (fopen_s(&Save, "Data/Hiscore.txt", "w") != 0)
	{
		return EXIT_FAILURE;
	}
	if (Save)
	{
		fprintf(Save, "%d", _score);

		fclose(Save);
	}
}