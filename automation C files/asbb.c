/******
 *
 *  asbb.c 
 *  Robert Clark, ebobtron
 *  
 *   CS50x  winter/spring 2014 with launchcode
 *  
 *  automate the testing and posting of submissions to the Leader Board
 *
 ******/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "hidden.h"
#include "functions.h"

// some globals
unsigned short int MYSTRINGSIZE = 255;
unsigned short int MYIDSIZE = 4;

int main(int argc, char* argv[])
{
    // option arg one = -sl
    
    char testVersion[8];
    strcpy(testVersion, "test");
    
    if(argc > 1) 
        
        if(!strcmp(argv[1], "-sl")) {
        
            strcpy(testVersion, "testsl");
            printf(".......testversion %s\n\n", testVersion);
        }
  
    // variable and structure defines
    char stringBuf[255];
    
    // splash the screen start the program
    splash();
    sleep(1);
    
    // we need a download folder 
    while(glob("downloaded", 0, NULL, &SUBDATA)) {
    
        printf("\n....    download directory not found\n" );
        sleep(2);
        printf("\33[1A....    making directory \" download \"\n");
        sleep(1);
        system("mkdir downloaded");
    }
    
    // create command string for wget   
    sprintf(stringBuf,"wget -a wgetlog.txt -v --config=config.txt");
   
    // security exclusion.
    // create config file for wget
    // createConfig();

    // download submission files
    int result = system(stringBuf);    

    // remove config.txt to safeguard security data
    // system("rm -f config.txt");
    
    // display ftp errors if any and close
    if(!result) {
    
        printf("\n....    Download Attempt Completed\n");
    }    
    else {
    
        printf("SYSTEM ERROR CODE = %i, consult documention.\n", result);
        
        // clean up and go
        system("rm -f downloaded/*");
        system("rmdir downloaded");    
                                                           
        if(&SUBDATA)
            globfree(&SUBDATA);
        
        return 1;
    }
    
    sleep(2);
    
    checkDownloaded();
    
    bool valid[SUBDATA.gl_pathc];
    bool canSpell[SUBDATA.gl_pathc];
    char file[SUBDATA.gl_pathc][MYSTRINGSIZE + 1];
    char id[SUBDATA.gl_pathc][MYIDSIZE + 1];
    char name[SUBDATA.gl_pathc][MYSTRINGSIZE + 1];
    char email[SUBDATA.gl_pathc][MYSTRINGSIZE + 1];
    
    char sbuf[256];
    int subcount = 0;
    
    FILE* infile = fopen("downloaded/subInfo.txt","r");
    fgets(sbuf ,sizeof(sbuf), infile);
    for(int i = 0; !feof(infile);i++) {
        
        //reference use %[^,], for csv files
        
        sscanf(sbuf,"%[^,],%[^,],%[^,],%[^,]", file[i], id[i], name[i], email[i]);
        email[i][strlen(email[i]) - 1] = '\0';
        
        printf("....    Submission Id: %s  Name: %s  \n", id[i], name[i]);
        
        subcount ++;
        
        fgets(sbuf ,sizeof(sbuf), infile);
    
    }
    
    fclose(infile);
    if(SUBDATA.gl_pathc == subcount) {
    
    
        // set submission file permissions
        system("chmod 711 downloaded/*");
    }
    else {
        printf("    **** WARNING ** file count does not match recorded submissions  ***\n");
        printf("        .x files = %i Submission Text = %i\n", SUBDATA.gl_pathc, subcount);
        return 1;
    }
    
    /*/clean up
       system("rmdir downloaded");                                              
       if(&SUBDATA)
           globfree(&SUBDATA);
    
       return 2;               **********/

    
    if(SUBDATA.gl_pathc) {
        
        printf("\n....    Starting memory error and leak test with Valgrind\n");
    }
    
    system("rm -f runasbbtest.sh");
    
    for(int i = 0; i < SUBDATA.gl_pathc; i++) {
        
        // create valgrind command string
        sprintf(stringBuf,"valgrind --log-file=vdump.txt ./downloaded/%s \
                       dracula.txt > sresults.txt", file[i]);
        // run valgrind
        system(stringBuf);

        // add a pretty
        printf("\n");
        
        // open output files 
        FILE* outfilePass = fopen("pass.txt","a");
        FILE* outfileFail = fopen("fail.txt","a");
        FILE* outfileNote = fopen("emailNot.txt", "a");

        // temporary file handle holder
        FILE* outfile = NULL;
                
        
        // parse the valgrind dump for erorrs and memory usage
        // then print and store results of test
        if(parseVal()) {            
            
            printf("        %s passed Valgrind testing -> reports %s MBytes\n", \
                               id[i], valResults);
            
            sprintf(stringBuf, "%s, %s\n", name[i], valResults);
            fwrite(stringBuf, strlen(stringBuf), 1, outfilePass);
            valid[i] = true;
            outfile = outfilePass;
            
            if(outfileFail) {
                fclose(outfileFail);
            }
        }
        else {
        
            printf("        %s failed Valgrind testing reports %s\n", id[i], valResults);
            
            sprintf(stringBuf, "%s, failed valgrind: %s \n", name[i], valResults);
            fwrite(stringBuf, strlen(stringBuf), 1, outfileFail);
            outfile = outfileFail;
            valid[i] = false;
            
            if(outfilePass) {
                fclose(outfilePass);
            }
        }

        if(spelling()) {
        
            sprintf(stringBuf, "        %s -> %s\n", id[i], spellerResults);
            printf("%s", stringBuf);
            fwrite(stringBuf, strlen(stringBuf), 1, outfile);
            canSpell[i] = true;
            sprintf(stringBuf,"mv downloaded/%s pass", file[i]);
            system(stringBuf);
              
            }
            else {
            
                sprintf(stringBuf, "        %s -> %s\n", id[i], spellerResults);
                printf("%s", stringBuf);
                fwrite(stringBuf, strlen(stringBuf), 1, outfile);
                canSpell[i] = false;
                sprintf(stringBuf,"mv downloaded/%s failed", file[i]);
                system(stringBuf);
            }
            
        // create email notifacations
        if(valid[i] && canSpell[i]) {
            
            fprintf(outfileNote,"%s,%s,%s\n",email[i], "from", "Leader Board");
            fprintf(outfileNote,"  %s, id: %s, %s\n", name[i], id[i], \
                        "Welcome to the Leader Board,");
            
            }
            else {
            
            fprintf(outfileNote,"%s,%s,%s\n",email[i], "from", "Leader Board");
            fprintf(outfileNote,"%s - %s -%s\n", \
               "Sorry, your submission failed valgind and/or a spelling check", \
                valResults, spellerResults);
            }
        
        // prepare bash script for testing.
        FILE* bashHan = fopen("runasbbtest.sh", "a");
        
        if(i == 0) {
            fprintf(bashHan,"#!/bin/bash\n\n");
            }
        
        if(valid[i] && canSpell[i]) {
            
            fprintf(bashHan,"counter=$1\nwhile [ $counter -gt 0 ]\ndo\n\n");
            fprintf(bashHan,"./%s ./pass/%s %s %s %s\n\n", \
                             testVersion, file[i], id[i], name[i], valMemory);
            fprintf(bashHan,"counter=$(( $counter - 1 ))\ndone\necho done testing %s\n\n", id[i]);
        }
        
        if(i == SUBDATA.gl_pathc - 1) {
            fprintf(bashHan,"\n./parSub");
        }
        
        
        fclose(bashHan);
        
        
        if(outfile) {
            fclose(outfile);
            }
        if(outfileNote) {
            fclose(outfileNote);
            }    
        
        
        // TODO cleanup dump result files for next test.
    }
    
     // set permission remove files and downloaded directory
    system("chmod 711 *.sh"); 
    system("rm -f downloaded/*");
    system("rmdir downloaded");
                                                           
    if(&SUBDATA)
        globfree(&SUBDATA);
    
    int numberofTests = 0;
    
    if(argc > 1) {
        
        numberofTests = atoi(argv[1]);
    
        if(!strcmp(argv[1], "-sl")) {
        
            printf("\n....    done, bye!\n \
                 \n....    You need to run runasbbtest.sh manually to complete testing \
                 \n*********************************************************************\
                 \n\n\n");
            return 0;     
                
        }
    }
    
    if(numberofTests < 1) {
        numberofTests = 1;
    }
    
    char comString[26];
    
    printf("\n....    Starting benchmark tests.....\n");
    
    sprintf(comString,"./runasbbtest.sh %i", numberofTests);
    system(comString);
    
    
    printf("\n....   testing...   done, bye!\n\n");
    
    return 0;

}
                                             
    
    
    
    
    




