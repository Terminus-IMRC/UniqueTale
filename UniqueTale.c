#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error(const char *str);

int main(int argc, char *argv[])
{
	long turn;
	char toexclude[0xffff], str[0xffff];
	_Bool output_flag=0;
	FILE *fp_in, *fp_out, *res_fp;

	if(argc!=2)
		error("invalid arguments");

	fp_in=fopen(argv[1], "r");
	assert(fp_in);

	fseek(fp_in, 0L, SEEK_END);
	if(ftell(fp_in)==0L)
		error("input file is empty");
	fseek(fp_in, 0L, SEEK_SET);

	res_fp=fopen("result.txt", "w");
	assert(res_fp);

	for(turn=0; ; turn++){
		printf("turn:%ld\n", turn);

		sprintf(str, "turn%ld.txt", turn);
		fp_out=fopen(str, "w");
		assert(fp_out);

		fgets(toexclude, 0xffff, fp_in);
		fputs(toexclude, res_fp);
		fflush(res_fp);

		while(!feof(fp_in)){
			fgets(str, 0xffff, fp_in);
			if(strcmp(toexclude, str)){
				output_flag=1;
				fputs(str, fp_out);
			}
		}

		fclose(fp_in);
		fclose(fp_out);

		if(turn!=0){
			sprintf(str, "turn%ld.txt", turn-1);
			remove(str);
		}

		if(!output_flag){
			sprintf(str, "turn%ld.txt", turn);
			remove(str);
			break;
		}
		output_flag=0;

		sprintf(str, "turn%ld.txt", turn);
		fp_in=fopen(str, "r");
		assert(fp_in);
	}

	fclose(res_fp);

	return 0;
}

void error(const char *str)
{
	fprintf(stderr, "error: %s\n", str);

	exit(EXIT_FAILURE);
}
