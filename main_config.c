#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define INI_FILE  "Ini_File_lR5400.txt"
 	 
unsigned int parse_int_value(char* name, unsigned int* value)
{
    char buffer[100];
    char* p_buffer;
    int parse_result = 0;
	
    FILE *fp = fopen(INI_FILE, "r");                 // do not use "rb"
    if (fp == NULL)
    {
    	printf("File not found");
    	return 0;
	}
    while (fgets(buffer, sizeof(buffer), fp) && (parse_result == 0)) 
	{
      p_buffer = strstr(buffer, name);
      if (p_buffer == buffer)
      {
    	p_buffer += strlen(name);
    	parse_result = sscanf(p_buffer, "=%u", value);
      }
    }
    fclose(fp);
    return parse_result;
}

unsigned int parse_string(char* name, char* str_value, int buf_size)
{
    char buffer[100];
    char str[20];
    char* p_buffer;
    int parse_result = 0;
    
    FILE *fp = fopen(INI_FILE, "r");                 // do not use "rb"
    if (fp == NULL)
    {
    	printf("File not found");
    	return 0;
	}
    while (fgets(buffer, sizeof(buffer), fp) && (parse_result == 0)) 
	{
    	p_buffer = strstr(buffer, name);
    	if (p_buffer == buffer)
    	{
    		p_buffer += strlen(name);
    		parse_result = sscanf(p_buffer, "=%s", str);

    		if (parse_result == 1 ) 
			{
	  			strncpy(str_value, str, buf_size-1);
			}
	    }
    }
    fclose(fp);
	return parse_result;
}


unsigned int antenna = 2;
char region [10] = "EU";
unsigned int min_q = 3;
unsigned int power = 1000;
unsigned int max_queries = 4;

int main (void)
{
    int rc;
   
    printf("Defaultvalues:\n");
    printf("Antenna=%d\n", antenna);
    printf("Region=%s\n", region);
    printf("Min_Q=%d\n", min_q);
    printf("Transmit_Power_DBM=%d\n", power);
    printf("Max_Queries_Since_Valid_EPC=%d\n\n", max_queries);
      
	rc = parse_int_value("Antenna", &antenna);
    if (rc == 0)
      printf("Error\n");
    else
    {
      printf("Antenna=%d\n", antenna);
	}
	
	rc = parse_string("Region", region, sizeof(region));
    if (rc == 0)
      printf("Error\n");
    else
    {
      printf("Region=%s\n", region);
	}
	
	rc = parse_int_value("Min_Q", &min_q);
    if (rc == 0)
      printf("Error\n");
    else
    {
      printf("Min_Q=%d\n", min_q);
	}
	
	rc = parse_int_value("Transmit_Power_DBM", &power);
    if (rc == 0)
    {
      printf("Error\n");
    }
    else
    {
      printf("Transmit_Power_DBM=%d\n", power);
	}
	
	rc = parse_int_value("Max_Queries_Since_Valid_EPC", &max_queries);
    if (rc == 0)
    {
      printf("Error\n");
    }
    else
    {
      printf("Max_Queries_Since_Valid_EPC=%d\n", max_queries);
	}
	
    return 0;
}

