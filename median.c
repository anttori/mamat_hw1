#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {//method to use for sorting
    return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[]){
    FILE *f=stdin;//grades input inisilized to stdin
    if(strcmp(argv[1],"-")){//if there isnt "-" argument instead of path
        f=fopen(argv[1],"r");//open file
    }
    int *arr=NULL;//grade array
    int lines_counter=0;//what line do we prosses  currently
    int return_value_for_scan;//scan may return end of file and eroor
    int grade;//the current grade prossesed
    while(1){
        return_value_for_scan=fscanf(f,"%d",&grade);
        if(return_value_for_scan==EOF){//if end of file
            break;
        }else if(return_value_for_scan!=1||grade<0||grade>100){//if invalid input
            //error
            lines_counter++;
            fprintf(stderr,
                "Error at line %d: invalid input %d",lines_counter,grade );//error message to stderr
            return 1;//ערך שגיאה של מערכת ההפעלה
            
            
        }else {
            lines_counter++;
            arr=realloc(arr, lines_counter * sizeof(int));//re allocate sapce according to new size;
            arr[lines_counter-1]=grade;//adding the fraded to the array
        }
    }
    if (f != stdin) fclose(f);
    qsort(arr,lines_counter,sizeof(int),compare_ints);//sorting the grades
    fprintf(stdout,"%d",arr[(lines_counter+1)/2-1]);//printing the median 
}
