#include <sys/utsname.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAG   "\033[01;35m"
#define BLU  "\033[01;37m"
#define RED "\033[22;31m"
#define YEL "\033[01;33m"
#define GRE "\033[01;32m"

///int split_input(char b[], char modified[10][10]){

	//char *token;
	

	//int i=0;
	//while ((token = strtok_r(b, " ", &b))){
	//	strcpy(modified[i],token);
//		printf("i= %d\n",i);
      //  i++;
	//}





//	int x=0; int y=0;
//	for(int i=0; i<strlen(b)+1; i++){
//		if(b[i]==' ' || b[i]=='\0'){
//			modified[x][y]='\0';
//			x++;
//			y=0;
//		}
//		else{
//			modified[x][y]=b[i];
//			y++;
//		}
//	}

//	for(int i=0; i<x; i++){						// loop to check output
//		printf("%s\n",modified[i]);
//	}
//	return i;
//}


int main(int argc, char *argv[], char * envp[]){
//	system("@cls||clear");

	printf("\n");
	printf(YEL "<<<---Welcome to the doof_shell--->>>\n");
	printf("\n");
//	int status = 0;
	int error=0;
	int result=2;
	int len;
	int flag=0;
	char input[100]=" ";
	char parsed[100][100];
	char cur_dir[1024];
	char org_dir[1024];
	char shell_name[50]="doof_shell";
	char hist[100][100];
	int histo=0;


   // char prompt_1[50];
    char prompt_2[50]="";
	getcwd(org_dir,sizeof(org_dir));		// for shell in shell & help
    struct utsname name;
	if(uname(&name)) exit(-1);
	strcat(prompt_2,name.sysname);
	strcat(prompt_2,"@");
	strcat(prompt_2,name.release);
	char *prompt_1=getenv("USER");
//	printf("Your computer's OS is %s@%s\n", name.sysname, name.release);

	while(1){
		
  //  	int y=0;
    //	for(int x=16; envp[26][x] != '\0'; x++,y++){
    //	//	printf("%c",envp[16][x] );
    //		prompt_2[y]=envp[26][x];
    //	}

		
		getcwd(cur_dir,sizeof(cur_dir));    	

    	printf(YEL "[");
    	printf(MAG"%s",prompt_1);
		printf(YEL "] ");
		printf("{");
		printf(GRE"%s",cur_dir);
		printf(YEL"}\n");

		printf("(");
		printf(MAG"%s",prompt_2);
		printf(YEL ")~>" BLU);

		//	printf("()~>" BLU);							// prompt
		scanf("%[^\n]%*c",input);				// take input
		

	//	printf("Len of input %d",strlen(input));

		if(strlen(input) == 0 ){
		//	char r='';
		//	input[1]=r;
	//		error=1;
	//		printf("no input BC \n");
			memset(input, 0, sizeof input);
			char input[100]=" ";

		}

		
		printf(GRE);


		strcpy(hist[histo],input);				// copy input to history
	//	printf("Check hist %s\n",hist[histo]);
		histo++;


		char *token;
		char* rest = input;
		int i=0;
		while ((token = strtok_r(rest, " ", &rest))){
			strcpy(parsed[i],token);
	    	i++;
		}

		//printf("parsed[0] %s\n",parsed[0]);
		//printf("parsed[1] %s\n",parsed[1]);
		//printf("parsed[2] %s\n",parsed[2]);
		//printf("i = %d\n",i);

			

		if(strcmp(parsed[0],"exit")==0){				// compare if input = exit
			printf(RED"May the SATAN bless U  \\__(^-^)__/\n");
			exit(0);
		}
									

//		len=split_input(input,parsed);			// split str in 2d array
		printf(GRE);
		if(strcmp(parsed[0],"history")==0){		// history
			for(int x=0; x<histo; x++)
				printf(GRE"%s\n",hist[x]);
				flag++;
		}


		if(strcmp(parsed[0],"echo")==0){		// echo
			int x = 1;
			int param = x;
			if(parsed[1][0] == 45){
				param = 2;
				x = 2;
			}
			for(; x<i; x++){
				if(strcmp(parsed[x],"\"")==0)
					continue;
	
				printf(" ");
				for(int y=0; y<strlen(parsed[x]); y++){
					if(parsed[x][y]==34)
						continue;
					printf(GRE"%c",parsed[x][y]);
				}
				
			}
			if(param != 2)
			printf("\n");
			flag++;
		}

		if(strcmp(parsed[0],"pwd")==0){			// pwd
			getcwd(cur_dir,sizeof(cur_dir));
			printf(BLU"%s\n",cur_dir);
			flag++;
		}


		if(strcmp(parsed[0],"help")==0){			// help maalik
			char ch, file_name[25];
    		FILE *fp;
 			//getcwd(org_dir,sizeof(org_dir));
 			strcat(org_dir,"/help.txt");
		    fp = fopen(org_dir, "r"); // read mode
        	while((ch = fgetc(fp)) != EOF)
            	printf(BLU"%c",ch);
        		printf("\n");
    		fclose(fp);
   		
			flag++;
		}


		//printf("%s",parsed[0]);
		if(strcmp(parsed[0],"cd")==0){			// cd
			if(parsed[1][0] == '\0'){
				char temp[100]="/home/";
				char *p=getenv("USER");
				strcat(temp,p);
				//printf("temp %s\n",temp);
				chdir(temp);
			}
			else
				chdir(parsed[1]);
			getcwd(cur_dir,sizeof(cur_dir));
			
			printf(GRE"%s\n",cur_dir);
			flag++;
		}

		

	
		if(flag==0){
		char haha[] = "/bin/";
		strcat(haha,parsed[0]);

		result = access(haha,F_OK);	// check if in /usr/bin

/* 		for(int x=i; x<100; x++){
			parsed[x][0]='\0';
		}
		printf("Paresdd[2] %s\n",parsed[10]);

		char *argv[] = {parsed[0],parsed[1],parsed[2],parsed[3],parsed[4],parsed[5],parsed[6],parsed[7],parsed[8],parsed[9],parsed[10],parsed[11],NULL};
		//strcpy(argv[4],NULL);
		int pid = fork();
		printf("PID %d\n",pid);
			if(pid == 0){

				execvp(parsed[0],argv);
			}
*/	

		int pid = fork();
			if(pid == 0){
				printf(GRE);

		//		if(strcmp(parsed[0],"doof_shell")==0){				// compare if input = shell
		//			execl(org_dir,shell_name,NULL);
			
		//		}
					char *abcd[200];
					int z=0;
					for(; z<i; z++)
						abcd[z] = parsed[z];
					abcd[z]=NULL;
					execvp(abcd[0],abcd);

				
				printf("\n");
			}

//			char yoyo[100][200];
//			for(int a=0; a<i; a++){
//				strcpy(yoyo[a],parsed[a]);
//				printf("This is yoyo %s\n",yoyo[a]);
//			}
//			strcpy(yoyo[i],NULL);
			// printf("abcde");
			// strcpy(parsed[i],NULL);

			// for(int x=0; x<i; x++){
			// 	printf("This is parsed %s\n",parsed[x]);
			// }


//			execvp(parsed[0],parsed);




//			char yoyo[100]="haha";	
//			for(int a=0; a<i; a++){
//				exe	


//			} 
//			printf("%s\n",yoyo);
//
///			execl(yoyo,NULL);
/* 			char yoyo[100]="";
			strcpy(yoyo,parsed[0]);
			for(int a=1; a<i; a++){
				strcat(yoyo,",");
				strcat(yoyo,parsed[a]);
				}
				printf("%s\n",yoyo);
				execl(haha,yoyo,NULL);
			
	*/		
			
			else
				{
					wait(0);
				}
				
		
	//			else
	//			{
	//			execl("/usr/bin/ls","ls",NULL);
	//				}
				flag++;

		}

/* 

		else if(strcmp(parsed[0],"ls")==0){			// ls
			
			int pid = fork();
			printf("%d\n",pid);
			if(pid == 0){
				if(parsed[1][0] != '\0'){
					printf("null hai \n");
					execl("/usr/bin/ls","ls",parsed[1],NULL);
					}

				else
				{
				execl("/usr/bin/ls","ls",NULL);
					}
				
				



//				if(strcmp(parsed[1],"-l")==0){
//					printf("pooch gaya");
//					char *arr[] = {"/home/maalik/Desktop/doof_shell/ls",parsed[0],parsed[1]};
//					execvp(arr[0],arr);
//				}
			}
			else
			{
				wait(0);
			}	
		}

		else if(strcmp(parsed[0],"cat")==0){
			int pid = fork();
			if(pid == 0){
				printf("pooch gaya\n");

				if(parsed[2][0] != '\0'){
					printf("null hai \n");
					execl("/usr/bin/cat","cat",parsed[1],parsed[2],NULL);
				}
				else
				{
					execl("/usr/bin/cat","cat",parsed[1],NULL);
				}
				

			//	execl("/usr/bin/cat","cat",parsed[1],parsed[2],NULL);
			//	char *arr[] = {"/home/maalik/Desktop/doof_shell/cat",parsed[0],parsed[1]};
			//	execvp(arr[0],arr);
			}
			else{
				wait(0);
			}
		}

		else if(strcmp(parsed[0],"mkdir")==0){
			int pid = fork();
			if(pid == 0){

				if(parsed[2][0] != '\0'){
					printf("null hai \n");
					execl("/usr/bin/mkdir","mkdir",parsed[1],parsed[2],NULL);
				}
				else
				{
					execl("/usr/bin/mkdir","mkdir",parsed[1],NULL);
				}
				
			 }
			else{
				wait(0);
			}
		}

		else if(strcmp(parsed[0],"rm")==0){
			int pid = fork();
			if(pid == 0){
				if(parsed[2][0] != '\0'){
					printf("null hai \n");
					execl("/usr/bin/rm","rm",parsed[1],parsed[2],NULL);
					}
				else
					{
					execl("/usr/bin/rm","rm",parsed[1],NULL);
					}

			}

			else{
				wait(0);
			}
		}

		else if(strcmp(parsed[0],"date")==0){
			int pid = fork();
			if(pid == 0){

				if(parsed[1][0] != '\0'){
					printf("null hai \n");
					execl("/usr/bin/date","date",parsed[1],NULL);
					}
				else
					{
					execl("/usr/bin/date","date",NULL);
					}



			}
			else{
				wait(0);
			}
		}



*/

			if(result==-1)
			printf(RED "Wrong input format!!! Type \"help maalik\" for help, or consult the creator (*-*)\n");
		

		memset(parsed, 0, sizeof parsed);
		memset(input, 0, sizeof input);
		flag=0;
		result=2;	
		error=0;
	}

	return 0;
}

