
%{
 #include<stdio.h>
 #define size 40
 #define maxentries 20

	int globalnary=0;
	int namingctr=1;
	char canthelpit[size];	
	char databasename[size];
	char tablenames[maxentries][size];
	struct entityOrRelationIndex   // Primary Index Structure for ERHashTable
		{
		char name[size];
		int eorrflag;  // 0 for entity or 1 relation or 2 for weak entity
		struct entityOrRelationIndex *next;
		struct attributeBuckets *link;
		} *eorihead,*eoritemp,*eoritracer,*eoriutemp,*eoriutracer;
	
	struct attributeBuckets       // Buckets Structure for ERHashTable
		{
		char name[size];
		int primarykey; // 0 not or 1 yes
		int notnul;    // 0 or 1
		int unique;     // 0 or 1
		int type;       // 1,2,3,4,5,6,7,8,9,10,11,12
		int precision;  // value from program
		int scale;       // value from program
		int multiatt;    // 0 or 1
		int partkey;    // 0 or 1
		struct attributeBuckets *next;
		} *abhead,*abtemp,*abtracer,*abuhead,*abutemp,*abutracer;

	struct relationIndex         // Primary Index Structure for RelationHashTable
		{
		char name[size];
		int completed;        // checks whether the relation is resolved or not
		int n_ary;            // to store the number of entities participating in the relation
		int weakentityexists; // 1 for exists
		int identifyflag;        // 0 for not identify and 1 for identify
		struct relationIndex *next;
		struct entityInRelationBuckets *link;
		struct attributeBuckets *bucketlink;
		} *rihead,*ritemp,*ritracer;

	struct entityInRelationBuckets // Buckets Structure for RelationHashTable
		{
		char name[size];
		int fulldependent; // 0 not or 1 yes
		int weak;          // 0 or 1
		int arity;	   // number from program  
		struct entityInRelationBuckets *next;
		struct attributeBuckets *bucketlink;
		} *eirbhead,*eirbtemp,*eirbtracer;

	char *typenames[]={ "INTEGER","SMALL INT","NUMERIC","DECIMAL","DOUBLE","FLOAT","CHAR","VARCHAR","DATE",
			    "DATETIME","TIMESTAMP" };

	void ValidateAndCheck();
	void RestructureHashTable();
	void weakentitysolver();
        void MandNandnary();
        void PrintAndProcess();
	void checkandupdateweakentities(char[]);
	void attributebucketupdate(char *,int,int,int,int,int,int,int,int);
        void createHashIndexStructDef(char *,int);
        void fillList(char *,int,int,int,int,int);
        void createList(int,int,int);
        void createHashIndexRelation(char *,int);
        void createEntityList(char *,int,int);
        void printType(int,int,int);
	void displayStructures();
	void checklengthpreceision(char *,int length,int precision);
%}

%token vaavs sqbrop sqbrcl strut id
%token en rn curbrop curbrcl pk num  
%token notnull uni relation semicolon 
%token fd dbname mulv identify
%token integer smallint number decimal  wken
%token doub floa cha varchar dat partialkey
%token dattim timestamp linecounter 
%start S

%%
/* Conventions used in defining the grammar G=V,T,P,S are all caps words for set V-Variables or NonTerminals,
								          all small words for set T-Terminals,
									  S is the Start Symbol of the Grammar,
									  set P is defined as follows        */

/* Grammer We mean Production set starts from here */  

/* S is the Start Symbol of the Grammar,*/
 
S	 :   	
	 | vaavs sqbrop STMTS sqbrcl  // step 6 
	 ;

STMTS	 : 
	 | DBSTMT STDEFS REDEFS 
	 | DBSTMT STDEFS 
//	 | STDEFS REDEFS
//	 | STDEFS
	 | DBSTMT 
	 ;

DBSTMT	 : dbname id semicolon			 { strcpy(databasename,(char *)$2); }
	 ;

STDEFS   : STDEF
         | STDEFS STDEF
         ;

STDEF	 : strut id en curbrop DECLS curbrcl      {createHashIndexStructDef((char *)$2,0);}// 0 for   entity    step 3
	 | strut id rn curbrop DECLSRAS curbrcl   {createHashIndexStructDef((char *)$2,1);}// 1 for   relation  step 3
	 | strut id wken curbrop DECLWKS curbrcl  {createHashIndexStructDef((char *)$2,2);}// 2 for weak entity step 3
	 ;                                                                

DECLWKS  : DECLWK
	 | DECLWKS DECLWK
	 ;

DECLWK   : id TYPE semicolon             {fillList((char *)$1,0,0,0,0,0);} // step 2
	 | id TYPE partialkey semicolon  {fillList((char *)$1,0,0,0,0,1);} // fillList(name,pk,notnull,uni,mulv,parkey)
	 | id TYPE notnull semicolon     {fillList((char *)$1,0,1,0,0,0);}
	 | id TYPE mulv semicolon        {fillList((char *)$1,0,0,0,1,0);} 
	 ;

DECLSRAS : DECLSRA
	 | DECLSRAS DECLSRA
	 ;

DECLSRA	 : id TYPE semicolon              {fillList((char *)$1,0,0,0,0,0);} // step 2
	 | id TYPE notnull uni semicolon  {fillList((char *)$1,0,1,1,0,0);} // fillList(name,pk,notnull,uni,mulv,parkey)
	 | id TYPE uni notnull semicolon  {fillList((char *)$1,0,1,1,0,0);}
	 | id TYPE uni semicolon          {fillList((char *)$1,0,0,1,0,0);}  
	 | id TYPE notnull semicolon      {fillList((char *)$1,0,1,0,0,0);}
	 ;

DECLS    : DECL
	 | DECLS DECL
	 ;

DECL	 : id TYPE pk semicolon           {fillList((char *)$1,1,0,0,0,0);} // step 2
	 | id TYPE uni semicolon          {fillList((char *)$1,0,0,1,0,0);} // fillList(name,pk,notnull,uni,mulv,parkey)
	 | id TYPE notnull uni semicolon  {fillList((char *)$1,0,1,1,0,0);}
	 | id TYPE uni notnull semicolon  {fillList((char *)$1,0,1,1,0,0);}
	 | id TYPE semicolon              {fillList((char *)$1,0,0,0,0,0);}
	 | id TYPE notnull semicolon      {fillList((char *)$1,0,1,0,0,0);}
	 | id TYPE mulv notnull semicolon {fillList((char *)$1,0,1,0,1,0);}
	 | id TYPE notnull mulv semicolon {fillList((char *)$1,0,1,0,1,0);}
	 | id TYPE mulv         semicolon {fillList((char *)$1,0,0,0,1,0);}
	 ;

REDEFS   : REDEF
         | REDEFS REDEF
         ;

REDEF	 : relation id identify curbrop RSTMTS curbrcl {createHashIndexRelation((char *)$2,1);} // step 5 name,identify=1
	 | relation id          curbrop RSTMTS curbrcl {createHashIndexRelation((char *)$2,0);}
	 ;

RSTMTS   : RSTMT
	 | RSTMTS RSTMT
	 ;

RSTMT	 : id fd num semicolon      {createEntityList((char *)$1,1,atoi($3));}  // step 4 
	 | id num fd semicolon      {createEntityList((char *)$1,1,atoi($2));}
	 | id    num semicolon      {createEntityList((char *)$1,0,atoi($2));}  //createEntityList(name,fd,arity);
	 | id fd     semicolon      {createEntityList((char *)$1,1,0);       }
	 | id        semicolon      {createEntityList((char *)$1,0,0);       }
	 ; 

/* carry on to complete the grammar for the problem domain */
 
TYPE	 : integer                     {createList(1,0,0);}                    // step 1
	 | smallint                    {createList(2,0,0);}                    //createList(type,precision scale);
	 | number     num num          {checklengthpreceision((char *)$1,atoi($2),atoi($3));
						createList(3,atoi($2),atoi($3));}
	 | decimal                     {createList(4,0,0);} 
	 | doub       num num          {checklengthpreceision((char *)$1,atoi($2),atoi($3));
					createList(5,atoi($2),atoi($3));} 
	 | floa                        {createList(6,0,0);}
	 | cha        num              {createList(7,0,atoi($2));}
	 | varchar    num              {createList(8,0,atoi($2));}
	 | dat                         {createList(9,0,0);}
	 | dattim                      {createList(10,0,0);}
	 | timestamp  num              {createList(11,0,atoi($2));}  
	 ;
%%

/* Write the code for main function to solve the problem set */

extern FILE *yyin;
yyerror(char *s)
	{
        fprintf(stderr,"vaavs found %s in %d Line Number\n",s,linecounter);exit(0);
        }

int main(int argc,char *argv[])
        {
	globalnary=0; //using again, this time for table names index
	FILE *fp,*fp1;
	fp=fopen(argv[1],"r");
	yyin=fp;
        do
          {
          yyparse();
          }while(!feof(yyin));
        fclose(fp);
	RestructureHashTable();
	ValidateAndCheck();
//displayStructures(); This function is for debugging purpose to check whether the data structures are updated or not
	PrintAndProcess();
//displayStructures();
	fp=fopen("mo.sql","w");
	fp1=fopen("tablenames.vaas","w");
	fprintf(fp,"\n\tUSE %s ;",databasename);
	fprintf(fp,"\n\tSHOW TABLES ;");
	int i;
	for(i=0;i<globalnary;i++)
		{
		fprintf(fp,"\n\tDESCRIBE %s ;",tablenames[i]);
		fprintf(fp1,"%s\n",tablenames[i]);
		}
	fclose(fp);
	}

void ValidateAndCheck()
	{
	int checkflag=0;
	ritemp=rihead;
	while(ritemp!=NULL)
		{
		eirbtemp=ritemp->link;
		while(eirbtemp!=NULL)
			{
			eoritemp=eorihead;
			while(eoritemp!=NULL)
				{
				if(!strcmp(eoritemp->name,eirbtemp->name))
					checkflag=1;
				eoritemp=eoritemp->next;
				}
			if(checkflag==1)
				checkflag=0;
			else
				{
				printf("\n\tThe entities to participate in relations are to be declared first\n"
				"\t\t\t\tCheck Out the Source file and define all entities participating in relations\n");
				exit(0);
				}
			eirbtemp=eirbtemp->next;
			}
		ritemp=ritemp->next;
		}
	int validationflag=0;
	eoritemp=eorihead;
	while(eoritemp!=NULL)
		{
		if(eoritemp->eorrflag==0) // validation for strong entities
			{
			abtemp=eoritemp->link;
			while(abtemp!=NULL)
				{
				if(abtemp->primarykey==1)
					validationflag=1;
				abtemp=abtemp->next;
				}
			if(validationflag==1)
				validationflag=0;
			else
				{
				printf("\n\t Check out the \"entitytype\" make sure they contain atleast one" 
				"\n\t\t\t\tprimary key or change them to \"weakentitytype\" if no primary key exists\n");
				exit(0);
				}
			}
		eoritemp=eoritemp->next;
		}
	eoritemp=eorihead;
	while(eoritemp!=NULL) // check for unique names in entities
		{
		eoritracer=eoritemp->next;
		while(eoritracer!=NULL)
			{
			if(!strcmp(eoritemp->name,eoritracer->name))
				{
				printf("\n\t Check out the \"naming of entities or weak entities or relations they should"
				       " not match\"\n\t\t\tSo do use different names for them\n"
					" \"%s\" name repeated\n ",eoritemp->name);
				exit(0);
				}	
			//printf("\n %s %s ",eoritemp->name,eoritracer->name);
			eoritracer=eoritracer->next;
			}
		eoritemp=eoritemp->next;
		}
	eoritemp=eorihead;
	while(eoritemp!=NULL) // check for unique names among entities and relations
		{
		ritemp=rihead;
		while(ritemp!=NULL)
			{
			if(eoritemp->eorrflag!=1)
			if(!strcmp(eoritemp->name,ritemp->name))
				{
                                printf("\n\t Check out the \"naming of entities or weak entities or relations they should"
                                       " not match\"\n\t\t\tSo do use different names for them\n"
					" \"%s\" name repeated\n ",eoritemp->name);
                                exit(0);
                                }
			ritemp=ritemp->next;
			}
		eoritemp=eoritemp->next;
		}
	ritemp=rihead;
	while(ritemp!=NULL)  //check for unique names among relations
		{
		ritracer=ritemp->next;
		while(ritracer!=NULL)
			{
			if(!strcmp(ritracer->name,ritemp->name))
				{
				printf("\n\t Check out the \"naming of entities or weak entities or relations they should"
                                       " not match\"\n\t\t\tSo do use different names for them\n"
					"\" %s\" name repeated\n ",ritracer->name);
                                exit(0);
                                }
			ritracer=ritracer->next;
			}	
		ritemp=ritemp->next;
		}
	ritemp=rihead;
        while(ritemp!=NULL)
                {
                if(ritemp->n_ary<2)
			{
			printf("\n \"%s\" Relation ship cannot be possible\n " 
			       "make sure a relation contains atleast two participating entities" 
				"\nif recursive also specify them\n");
			exit(0);
			}
                ritemp=ritemp->next;
                }
	}

void createHashIndexStructDef(char *eorrname,int entityorrelationorweak)
	{
	if(eorihead==NULL)
		{
		eorihead=(struct entityOrRelationIndex *)malloc(sizeof(struct entityOrRelationIndex));
		strcpy(eorihead->name,eorrname);
		eorihead->eorrflag=entityorrelationorweak;
		eorihead->next=NULL;
		eorihead->link=abhead; // creation of hash linking starts
		abhead=NULL; // making it null to create other buckets of next relation or entities
		}
	else
		{
		eoritemp=(struct entityOrRelationIndex *)malloc(sizeof(struct entityOrRelationIndex));		
		strcpy(eoritemp->name,eorrname);
		eoritemp->eorrflag=entityorrelationorweak;
		eoritemp->next=NULL;
		eoritemp->link=abhead;
		abhead=NULL;
		eoritracer=eorihead;
		while(eoritracer->next!=NULL)
			{
			eoritracer=eoritracer->next;
			}
		eoritracer->next=eoritemp;
		}
	}

void fillList(char *attributename,int primarykey,int notnul,int unique,int mulva,int partky)
	{
	abtracer=abhead;
	while(abtracer->next!=NULL)
		{
		abtracer=abtracer->next;
		}
	abtemp=abtracer;
	strcpy(abtemp->name,attributename);
	abtemp->multiatt=mulva;
	abtemp->partkey=partky;
	abtemp->primarykey=primarykey;
	abtemp->notnul=notnul;
	abtemp->unique=unique;
	}

void createList(int type,int precision,int scale)
	{
	if(abhead==NULL)
		{
		abhead=(struct attributeBuckets *)malloc(sizeof(struct attributeBuckets));
		abhead->type=type;
		abhead->precision=precision;
		abhead->scale=scale;
		abhead->next=NULL;
		}
	else	
		{
		abtemp=(struct attributeBuckets *)malloc(sizeof(struct attributeBuckets));
		abtemp->type=type;
                abtemp->precision=precision;
                abtemp->scale=scale;
                abtemp->next=NULL;
		abtracer=abhead;
		while(abtracer->next!=NULL)
			{
			abtracer=abtracer->next;
			}
		abtracer->next=abtemp;
		}
	}

void createHashIndexRelation(char *relationname,int ident)
	{
	if(rihead==NULL)
		{
		rihead=(struct relationIndex *)malloc(sizeof(struct relationIndex));
		strcpy(rihead->name,relationname);
		rihead->identifyflag=ident; // 1 for identifying relationship
		rihead->n_ary=globalnary; globalnary=0; 
		rihead->next=NULL;
		rihead->link=eirbhead;
		eirbhead=NULL;
		}
	else
		{
		ritemp=(struct relationIndex *)malloc(sizeof(struct relationIndex));
		strcpy(ritemp->name,relationname);
		ritemp->identifyflag=ident; // 1 for identifying relationship
		ritemp->n_ary=globalnary; globalnary=0;
		ritemp->next=NULL;
		ritemp->link=eirbhead;
		eirbhead=NULL;
		ritracer=rihead;
		while(ritracer->next!=NULL)
			{
			ritracer=ritracer->next;
			}
		ritracer->next=ritemp;
		}
	}

void createEntityList(char entityname[],int totalpart,int arity)
	{
	if(eirbhead==NULL)
		{
		eirbhead=(struct entityInRelationBuckets *)malloc(sizeof(struct entityInRelationBuckets));
		strcpy(eirbhead->name,entityname);
		eirbhead->fulldependent=totalpart;
		//eirbhead->weak=weak;
		eirbhead->arity=arity;
		eirbhead->next=NULL;
		globalnary++;
		}
	else
		{
		eirbtemp=(struct entityInRelationBuckets *)malloc(sizeof(struct entityInRelationBuckets));
                strcpy(eirbtemp->name,entityname);
                eirbtemp->fulldependent=totalpart;
                //eirbtemp->weak=weak;
                eirbtemp->arity=arity;
                eirbtemp->next=NULL;
		eirbtracer=eirbhead;
		while(eirbtracer->next!=NULL)
			{
			eirbtracer=eirbtracer->next;
			}
		eirbtracer->next=eirbtemp;
		globalnary++;
		}
	}

void RestructureHashTable()
	{
	ritemp=rihead;
	while(ritemp!=NULL)
		{
		eoritemp=eorihead;
		while(eoritemp!=NULL)
			{
			if(eoritemp->eorrflag==1) // 1 means relation
				{
				if(!strcmp(eoritemp->name,ritemp->name))
					ritemp->bucketlink=eoritemp->link;
				}
			else if(eoritemp->eorrflag==2 || eoritemp->eorrflag==0)
				{
				eirbtemp=ritemp->link;
				while(eirbtemp!=NULL)
					{
					if(!strcmp(eoritemp->name,eirbtemp->name))
						{
						eirbtemp->bucketlink=eoritemp->link;
						if(eoritemp->eorrflag==2) 
							{
							ritemp->weakentityexists+=1;
							eirbtemp->weak=1;//weak keyword in relation defination removal
							}
						}
					eirbtemp=eirbtemp->next;
					}				
				}
			eoritemp=eoritemp->next;
			}
		ritemp=ritemp->next;
		}
	}

void PrintAndProcess()
	{
	//Step 0 mapping of Database name
	printf("\n\tCREATE DATABASE %s ;\n",databasename);
	printf("\n\tUSE %s ;\n",databasename);
	//Step 1 mapping of Strong Entities
	int count=0;        
	eoritemp=eorihead;
	while(eoritemp!=NULL)
	   {
	   if(eoritemp->eorrflag==0) // only for strong entities 
		{   // To specify to generate the tables for entity structures not relation structures or weak entity
		printf("\n\tCREATE TABLE  %s  ( ",eoritemp->name);
		sprintf(tablenames[globalnary++],"%s\0",eoritemp->name);	
		abtemp=eoritemp->link; // intialize the initial buckets
		while(abtemp!=NULL) //This loop prints the attributes and their types with NOT NULL,UNIQUE Constraints
			{
			if(abtemp->multiatt==0) // make sure multi valued attributes are not considered
				{
				printf("\n\t\t%s ",abtemp->name);
				printType(abtemp->type,abtemp->precision,abtemp->scale);
				if(abtemp->notnul==1)
	                       		printf("     NOT NULL ");
				if(abtemp->unique==1)
					printf("     UNIQUE ");
				printf(",");
				}
			abtemp=abtemp->next;
			}
		printf(" \n\t\tPRIMARY KEY (");
		count=0;
		abtemp=eoritemp->link; // re initialize the initial bucket
                while(abtemp!=NULL) // This loop specifies the primary key constraints
			{
			if(abtemp->primarykey==1)
				{
				if(count==0)
					{
					printf("%s",abtemp->name);
				 	count++;
					}
				else
					printf(", %s",abtemp->name);
				}
			abtemp=abtemp->next;
			}
		printf(" ) );\n");
		}
	   eoritemp=eoritemp->next;
	   }
	// Step 2 resolve the weak entities 
	int identifyflag=0;
	while(identifyflag!=1)
		{
		identifyflag=1;
		ritemp=rihead;
		while(ritemp!=NULL)
			{
			if(ritemp->identifyflag==1)
				{
				//printf("\n\t\tidentify Relation name %s\n\n",ritemp->name);
				identifyflag=0;
				weakentitysolver();
				}
			ritemp=ritemp->next;
			}
		}
	int completionflag=0;
	while(completionflag!=1)
		{
		completionflag=1;	
		ritemp=rihead;
		while(ritemp!=NULL)
			{
			if(ritemp->weakentityexists==1)
				{
				//printf("\n\t\twk Relation name %s\n\n",ritemp->name);
				completionflag=0;
				weakentitysolver();
				}
			ritemp=ritemp->next;
			}
		}
	// Step 3 Resolve 1:1 relationships
	ritemp=rihead;
	while(ritemp!=NULL)
		{
		if(ritemp->n_ary==2)
			{
			int indexofnames=0;
		        char attrinames[maxentries][40];
			eirbtemp=ritemp->link; eirbtracer=eirbtemp->next;
			if(eirbtemp->arity==1 && eirbtracer->arity ==1)
				{
				//printf("\n\t\t1:1 Relation name %s\n\n",ritemp->name);
				//both fulldependent 
				if(eirbtracer->fulldependent==1 && eirbtemp->fulldependent==1)
					{
					int onlyonce=0;
									//step 3.1.3     both entities 
									//are fully dependent make a new table with 
									//name of relation foreign keys from both
                     							//entities pkeys and forming a composite 
									//primary key*********Com****done1********** 
					printf("\n\tCREATE TABLE %s_table (",ritemp->name);
					sprintf(tablenames[globalnary++],"%s_table\0",ritemp->name);
					while(eirbtemp!=NULL)
						{
						abtemp=eirbtemp->bucketlink;
						while(abtemp!=NULL)
							{
							if(abtemp->primarykey==1 && abtemp->multiatt==0)
								{
								printf("\n\t\t%sfk ",abtemp->name);
			                                        strcpy(attrinames[indexofnames++],abtemp->name);
                        			                printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        			printf(",");
								}
							abtemp=abtemp->next;
							}
						if(onlyonce==0)
                                			{ onlyonce=1;
                                			abtemp=ritemp->bucketlink; // go for all  attributes of relation
                                			while(abtemp!=NULL)
                                        			{
                                        			printf("\n\t\t%s ",abtemp->name);
                                        			printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        			printf(",");
                                        			abtemp=abtemp->next;
                                        			}
							}
						eirbtemp=eirbtemp->next;
						}
					count=0;
					int j=0;
        				printf("\n\t\tPRIMARY KEY ( ");
				       	for(j=0;j<indexofnames;j++)
				               	{
						if(count==0)
							{
							printf("%sfk",attrinames[j]);
							count++;
							}
				               	
					else
							printf(", %sfk ",attrinames[j]);
                				} 
					printf(" ),");
					count=0;
					eirbtemp=ritemp->link;
					while(eirbtemp!=NULL)
						{
						abtemp=eirbtemp->bucketlink;
                                               	while(abtemp!=NULL)
                                                       	{
                                                       	if(abtemp->primarykey==1) // if primary key
                                                               	{
								if(count==0)
									{
									count++;	
                                                                printf("\n\t\tFOREIGN KEY ( %sfk) REFERENCES  %s (%s) ",
                                                                        abtemp->name,eirbtemp->name,abtemp->name);
								printf(" ON DELETE CASCADE ON UPDATE CASCADE");
									}
								else
									{
							       	printf(",\n\t\tFOREIGN KEY ( %sfk) REFERENCES  %s (%s) ",
                                                                        abtemp->name,eirbtemp->name,abtemp->name);
                                                                printf(" ON DELETE CASCADE ON UPDATE CASCADE");
									}	
                                                               	}
                                                       	abtemp=abtemp->next;
                                                       	}
						eirbtemp=eirbtemp->next;
						}
					printf(" );\n");
					}
				//one of them is fullydependent
				else if(eirbtracer->fulldependent==1 || eirbtemp->fulldependent==1)
                                        {
									//step 3.1.2    fd=1 and wk=0  one relation fully
                                                                       //dependent if relation has no attributes shift
                                                                       //pkey from not fully dependent to fully dependent
									//***************************No*****done**********
					if(eirbtemp->fulldependent==1) 
						{ }
					else 
						{
						struct entityInRelationBuckets *swap;
						swap=eirbtemp; eirbtemp=eirbtracer;eirbtracer=swap;
						}
					abuhead=eirbtemp->bucketlink;// for attribute updater function
					printf("\n\tALTER TABLE %s ",eirbtemp->name);
					abtemp=eirbtracer->bucketlink;
					namingctr=namingctr+1;
					while(abtemp!=NULL)
						{
						if(abtemp->primarykey==1)
							{ 
                                                       	printf("\n\t\tADD COLUMN ( %s_%d ",abtemp->name,namingctr);
                                                       	printType(abtemp->type,abtemp->precision,abtemp->scale);
                                                       	printf(" ),");
                                                       	}
						abtemp=abtemp->next;
						}
					count=0;
				 	abtemp=eirbtracer->bucketlink; // go for all available attributes
                                        while(abtemp!=NULL)
                                               	{
                                               	if(abtemp->primarykey==1) // if primary key
                                                       	{
							if(count==0)
								count++;
							else
								printf(",");	
                                                       	printf("\n\t\tADD FOREIGN KEY ( %s_%d) REFERENCES  %s (%s)",
                                                       	abtemp->name,namingctr,eirbtracer->name,abtemp->name);
							sprintf(canthelpit,"%s_%d\0",abtemp->name,namingctr);
			                                attributebucketupdate(canthelpit,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
							printf(" ON DELETE CASCADE ON UPDATE CASCADE ");
							}
                                               	abtemp=abtemp->next;
                                               	}
					if(ritemp->bucketlink!=NULL)
						{
						abtemp=ritemp->bucketlink;
						while(abtemp!=NULL)
							{
							printf(",\n\t\tADD COLUMN ( %s  ",abtemp->name);
                                                	printType(abtemp->type,abtemp->precision,abtemp->scale);
                                                	printf(" )"); 
							attributebucketupdate(abtemp->name,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
					        	abtemp=abtemp->next;
							}
						}
					printf(" ;\n");
					}
				// general case
				else
					{
                						//step 3.1.4    fd=0 and wk=0 general case for all
								//remaining take one pkey as fkey into other table
                     						//in all the above cases if the relation does have
								//some attributes then shift them to altering table
								//************************Com********done1********
					abuhead=eirbtracer->bucketlink;// for attribute updater function
					printf("\n\tALTER TABLE %s ",eirbtracer->name);
	                                abtemp=eirbtemp->bucketlink;
					namingctr=namingctr+1;
        	                        while(abtemp!=NULL)
                	                        {
			 	                if(abtemp->primarykey==1)
                                	                {
                                        	        printf("\n\t\tADD COLUMN ( %s_%d ",abtemp->name,namingctr);
                                                	printType(abtemp->type,abtemp->precision,abtemp->scale);
                                                	printf(" ),");
                                                	}
                                        	abtemp=abtemp->next;
                                        	}
                                        abtemp=ritemp->bucketlink; // go for all  attributes of relation
                                        while(abtemp!=NULL)
                                            	{
                                                printf("\n\t\tADD COLUMN ( %s ",abtemp->name);
                                                printType(abtemp->type,abtemp->precision,abtemp->scale);
                                                printf(" ),");
						attributebucketupdate(abtemp->name,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
                                                abtemp=abtemp->next;
                                                 }
                                        abtemp=eirbtemp->bucketlink; // go for all available attributes
                                        count=0;
					while(abtemp!=NULL)
                                        	{
                                        	if(abtemp->primarykey==1) // if primary key
                                                	{
							if(count==0)
								count++;
							else 
								printf(",");	
                                                	printf("\n\t\tADD FOREIGN KEY ( %s_%d) REFERENCES  %s (%s)",
                                                	abtemp->name,namingctr,eirbtemp->name,abtemp->name);
							sprintf(canthelpit,"%s_%d\0",abtemp->name,namingctr);
							attributebucketupdate(canthelpit,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
							printf(" ON DELETE CASCADE ON UPDATE CASCADE");
                                                	}
                                        	abtemp=abtemp->next;
                                        	}
					printf(" ;\n");
					}
				}
			}
		ritemp=ritemp->next;
		}
	// Step 4 Resolve 1:N relationships
	ritemp=rihead;
        while(ritemp!=NULL)
                {
		//printf("\n%s %d ",ritemp->name,ritemp->identifyflag);
                if(ritemp->n_ary==2 && ritemp->identifyflag==0 && ritemp->completed==0)
                        {
			eirbtemp=ritemp->link; eirbtracer=eirbtemp->next;
			if((eirbtracer->arity!=1 && eirbtemp->arity==1)||(eirbtracer->arity==1 && eirbtemp->arity!=1))
				{ 					
				//printf("\n\t\t1:N Relation name %s\n\n",ritemp->name);
				//printf("\n%s is a 1:N Relationship",ritemp->name);
				if(eirbtracer->arity==1)
					{
					struct entityInRelationBuckets *swap;
					swap=eirbtemp;eirbtemp=eirbtracer;eirbtracer=swap;
					}
				abuhead=eirbtracer->bucketlink;// for attribute updater function
                                int updaterflag=0;
				printf("\n\tALTER TABLE %s ",eirbtracer->name);
				abtemp=eirbtemp->bucketlink;
				namingctr=namingctr+1;
				while(abtemp!=NULL) 
					{
					if(abtemp->primarykey==1)
						{
						printf("\n\t\tADD COLUMN (  %s_%d ",abtemp->name,namingctr);
                                        	printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        	printf(" ),");
                                        	}
                                	abtemp=abtemp->next;
					}
                                abtemp=ritemp->bucketlink; // go for all  attributes of relation
                                while(abtemp!=NULL)
                                	{
                                        printf("\n\t\tADD COLUMN ( %s ",abtemp->name);
                                        printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        printf(" ),");
					attributebucketupdate(abtemp->name,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
                                        abtemp=abtemp->next;
                                        }
                        	abtemp=eirbtemp->bucketlink; // go for all available attributes
				count=0;
                        	while(abtemp!=NULL)
                                	{
                                	if(abtemp->primarykey==1) // if primary key
                                        	{
						if(count==0)
							count++;
						else
							printf(",");	
                                        	printf("\n\t\tADD FOREIGN KEY ( %s_%d) REFERENCES  %s (%s) ",
                                        	abtemp->name,namingctr,eirbtemp->name,abtemp->name);
					        sprintf(canthelpit,"%s_%d\0",abtemp->name,namingctr);
						attributebucketupdate(canthelpit,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
						printf(" ON DELETE CASCADE ON UPDATE CASCADE");
                                        	}
                                	abtemp=abtemp->next;
                                	}
				printf(" ;\n");
				}
                        }
                ritemp=ritemp->next;
                }
	// Step 5 Resolve M:N relationships
	ritemp=rihead;
        while(ritemp!=NULL)
                {
                if(ritemp->n_ary==2 && ritemp->completed==0)
                        {
			eirbtemp=ritemp->link; eirbtracer=eirbtemp->next;
			if(eirbtemp->arity!=1 && eirbtracer->arity!=1)
				{
				//printf("\n\t\t M:N Relation name %s\n\n",ritemp->name);
				MandNandnary();
				}
                        }
                ritemp=ritemp->next;
                }
	// Step 6 Resolve Multi Valued Attributes
     	eoritemp=eorihead;
        while(eoritemp!=NULL)
                {
                if(eoritemp->eorrflag==0)
                        {
                        abtemp=eoritemp->link;
                        while(abtemp!=NULL)
                                {
                                if(abtemp->multiatt==1)
                                        {
					abuhead=NULL;
                                        printf("\n\tCREATE TABLE %s_%s ( ",eoritemp->name,abtemp->name);
                                        sprintf(tablenames[globalnary++],"%s_%s\0",eoritemp->name,abtemp->name);
					printf("\n\t\t%s ",abtemp->name);
                                        printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        abtracer=eoritemp->link;
					printf(",");
                                        while(abtracer!=NULL)
                                                {
                                                if(abtracer->primarykey==1)
                                                        {
                                                        printf("\n\t\t%sfk ",abtracer->name);
                                                        printType(abtracer->type,abtracer->precision,abtracer->scale);
							printf(",");
                                                        }
                                                abtracer=abtracer->next;
                                                }
                                        abtracer=eoritemp->link;
                                	printf("\n\t\tPRIMARY KEY (");
					count=0;
                                        while(abtracer!=NULL)
                                                {
                                                if(abtracer->primarykey==1)
							{
							if(count==0)
								count++;
							else
								printf(",");	
                                                        printf("  %sfk ",abtracer->name);  
							}
                                                abtracer=abtracer->next;
                                                }
					printf(" )");
					abtracer=eoritemp->link;
					while(abtracer!=NULL)
						{
						if(abtracer->primarykey==1)
							{
							printf(",");
						        printf("\n\t\tFOREIGN KEY (%sfk) REFERENCES %s(%s)",abtracer->name
								,eoritemp->name,abtracer->name);
							printf(" ON DELETE CASCADE ON UPDATE CASCADE ");
							}
						abtracer=abtracer->next;
						}
                                   	printf(" );\n");   
				     }
                                abtemp=abtemp->next;
                                }
                        }
                eoritemp=eoritemp->next;
                }
	// Step 7 Resolve N_ary Relationships	
	ritemp=rihead;
        while(ritemp!=NULL)
                {
                if(ritemp->n_ary>2)
                        {
			MandNandnary();
                        }
                ritemp=ritemp->next;
                }
	}

void weakentitysolver()
	{
	int count=0;
	int indexofnames=0;
	char names[maxentries][40];
	//process 
	eirbtemp=ritemp->link;
	while(eirbtemp!=NULL)
		{
		if(eirbtemp->weak==1)
			{
			printf("\n\tCREATE TABLE  %s ( ",eirbtemp->name);
			sprintf(tablenames[globalnary++],"%s\0",eirbtemp->name);
			abtemp=eirbtemp->bucketlink;
			while(abtemp!=NULL)
				{
				if(abtemp->multiatt==0)
					{
					printf("\n\t\t%s ",abtemp->name);
					printType(abtemp->type,abtemp->precision,abtemp->scale);
                			if(abtemp->notnul==1)
                				printf("   NOT NULL ");
					printf(",");
					}
				abtemp=abtemp->next;
				}
			eirbtracer=ritemp->link;
			abuhead=eirbtemp->bucketlink;// note this
			while(eirbtracer!=NULL)
				{
				if(eirbtracer->weak==0)
					{
					abtemp=eirbtracer->bucketlink;
					while(abtemp!=NULL)
						{
						if(abtemp->primarykey==1 && abtemp->multiatt==0) 
                		                       	{
                                			printf("\n\t\t%s_%d ",abtemp->name,namingctr);
                                			strcpy(names[indexofnames++],abtemp->name);
                                			printType(abtemp->type,abtemp->precision,
							abtemp->scale);
							sprintf(canthelpit,"%s_%d\0",abtemp->name,namingctr);
							attributebucketupdate(canthelpit,abtemp->multiatt,abtemp->partkey,1,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
                                			printf(",");
                                			}
                                		abtemp=abtemp->next;	
						}
					}
				eirbtracer=eirbtracer->next;
				}
			if(ritemp->bucketlink!=NULL)
				{
				abuhead=eirbtemp->bucketlink;
				abtemp=ritemp->bucketlink;
				while(abtemp!=NULL)
					{
					printf("\n\t\t%s ",abtemp->name);
                                        printType(abtemp->type,abtemp->precision,
                                        abtemp->scale);
                                        attributebucketupdate(abtemp->name,abtemp->multiatt,abtemp->partkey,0,abtemp->notnul,abtemp->unique,abtemp->type,abtemp->precision,abtemp->scale);
                                        printf(",");
					abtemp=abtemp->next;
					}
				}
			count=0;
			printf("\n\t\tPRIMARY KEY ( ");int j;
                        for(j=0;j<indexofnames;j++)
                      		{
				if(count==0)
					count++;
				else	
					printf(",");		
                       		printf("  %s_%d ",names[j],namingctr);
                      		}
                        int partkeysetflag=0;
                        abtemp=eirbtemp->bucketlink;
                        while(abtemp!=NULL)
                              	{
                              	if(abtemp->partkey==1)
                                      	{
                                       	printf(", %s ",abtemp->name);
                                      	abtemp->primarykey=1;  abtemp->partkey=0; 
					partkeysetflag=1;
                                      	}
                                abtemp=abtemp->next;
                                }
			if(partkeysetflag==1)
                        	printf(" ),");
                        else 
                              	{
                               	abtemp=eirbtemp->bucketlink;
                              	while(abtemp!=NULL)
                                      	{
					if(abtemp->multiatt==0)
						{
                                      		printf(", %s ",abtemp->name);
                                      		abtemp->primarykey=1;
						}
                                      	abtemp=abtemp->next;
                                	}
				printf(" ),");
                        	}
			count=0;	
			eirbtracer=ritemp->link;
			while(eirbtracer!=NULL)
				{
				if(eirbtracer->weak==0)
					{
					abtemp=eirbtracer->bucketlink;
					while(abtemp!=NULL)
						{
						if(abtemp->primarykey==1 && abtemp->multiatt==0)
							{
							if(count==0)
								count++;
							else
								printf(",");
							printf("\n\t\tFOREIGN KEY ( %s_%d) REFERENCES  %s (%s)",
                                    	                abtemp->name,namingctr,eirbtracer->name,abtemp->name);
							printf(" ON DELETE CASCADE ON UPDATE CASCADE ");
							}
						abtemp=abtemp->next;
						}
					}
				eirbtracer=eirbtracer->next;
				}
			printf(" );\n");
			checkandupdateweakentities(eirbtemp->name);
			eirbtemp->weak=0;
			}
		eirbtemp=eirbtemp->next;
		}
	}

void MandNandnary()
	{
	int count=0;
	printf("\n\tCREATE TABLE %s_table ( ",ritemp->name);
	sprintf(tablenames[globalnary++],"%s_table\0",ritemp->name);
        int indexofnames=0,onlyonce=0;
        char names[maxentries][40];
        eirbtemp=ritemp->link;
        while(eirbtemp!=NULL) // go into entity in relation buckets
        	{ 
                if(eirbtemp->arity!=1) // only for m and n
			{
                	abtemp=eirbtemp->bucketlink; // go for all available attributes
                        while(abtemp!=NULL)
                              	{
                                if(abtemp->primarykey==1 && abtemp->multiatt==0) // if primary key
                                       	{
                                        printf("\n\t\t%sfk ",abtemp->name);
                                        strcpy(names[indexofnames++],abtemp->name);
                                        printType(abtemp->type,abtemp->precision,abtemp->scale);
                                        printf(",");
                                        }
                                abtemp=abtemp->next;
                                }
			if(onlyonce==0)
				{ onlyonce=1;
				abtemp=ritemp->bucketlink;  // go for all available attributes of relation
                       		while(abtemp!=NULL)
                               		{	
			       		printf("\n\t\t%s ",abtemp->name);
			       		printType(abtemp->type,abtemp->precision,abtemp->scale);
                               		printf(",");
			       		abtemp=abtemp->next;
			       		}
				}
			}
                eirbtemp=eirbtemp->next;
                }
        int j=0;
        printf("\n\t\tPRIMARY KEY ( ");
        for(j=0;j<indexofnames;j++)
             	{
		if(j!=0)
			printf(",");
                printf(" %sfk",names[j]); //abhinav removed , after fk Good Work man : Venkat :)
        	} 
	printf(" ),");
	eirbtemp=ritemp->link;
        while(eirbtemp!=NULL) // go into entity in relation buckets
                {
               // if(eirbtemp->arity!=1) // only for m and n
			{
                	abtemp=eirbtemp->bucketlink; // go for all available attributes
                        while(abtemp!=NULL)
                        	{
                        	if(abtemp->primarykey==1 && abtemp->multiatt==0) // if primary key
                        		{
					if(count==0)
						count++;
					else
						printf(",");		
                        		printf("\n\t\tFOREIGN KEY ( %sfk) REFERENCES  %s (%s)",
					abtemp->name,eirbtemp->name,abtemp->name);
					 printf(" ON DELETE CASCADE ON UPDATE CASCADE ");
                        		}
                        	abtemp=abtemp->next;
                        	}
                        }
		eirbtemp=eirbtemp->next;
		}
	printf(" );\n");
	}

void printType(int type,int precision,int scale)
	{
	switch(type)
        	{
	        case 1: printf(typenames[0]); break;
	        case 2: printf(typenames[1]); break;
        	case 3: printf(typenames[2]); printf("(%d,%d)",precision,scale); break;
    	        case 4: printf(typenames[3]); break;
	        case 5: printf(typenames[4]); printf("(%d,%d)",precision,scale); break;
        	case 6: printf(typenames[5]); break;
	        case 7: printf(typenames[6]); printf("(%d)",scale); break;
        	case 8: printf(typenames[7]); printf("(%d)",scale); break;
	        case 9: printf(typenames[8]); break;
	       	case 10: printf(typenames[9]); break;
        	case 11: printf(typenames[10]); printf("(%d)",scale); break;
        	}
	}

void attributebucketupdate(char *attributename,int mulva,int partky,int primarykey,int notnul,int unique,int type,
                           int precision,int scale)
        {
        if(abuhead!=NULL)
                {
                abutemp=(struct attributeBuckets *)malloc(sizeof(struct attributeBuckets));
                strcpy(abutemp->name,attributename);
                abutemp->multiatt=mulva;
                abutemp->partkey=partky;
                abutemp->primarykey=primarykey;
                abutemp->notnul=notnul;
                abutemp->unique=unique;
                abutemp->type=type;
                abutemp->precision=precision;
                abutemp->scale=scale;
                abutemp->next=NULL;
                abutracer=abuhead;
                while(abutracer->next!=NULL)
                        {
                        abutracer=abutracer->next;
                        }
                abutracer->next=abutemp;
                }
        else
                {
                abuhead=(struct attributeBuckets *)malloc(sizeof(struct attributeBuckets));
                strcpy(abuhead->name,attributename);
                abuhead->multiatt=mulva;
                abuhead->partkey=partky;
                abuhead->primarykey=primarykey;
                abuhead->notnul=notnul;
                abuhead->unique=unique;
                abuhead->type=type;
                abuhead->precision=precision;
                abuhead->scale=scale;
                abuhead->next=NULL;
                }
        }

void checkandupdateweakentities(char weakentityname[])
        {
	int onlyonce=0;
        struct relationIndex *ridup;
        struct entityInRelationBuckets *eirbdup;
        ridup=rihead;
        while(ridup!=NULL)
                {
                eirbdup=ridup->link;
                while(eirbdup!=NULL)
                        {
                        if(!strcmp(weakentityname,eirbdup->name))
				{
				if(onlyonce==0)
					{
					ridup->weakentityexists-=1;
					onlyonce=1;
					}
                                eirbdup->weak=0;
				}
			if(!strcmp(ridup->name,ritemp->name))
				{
				ridup->identifyflag=0;
				ridup->completed=1;
				}
                        eirbdup=eirbdup->next;
                        }
		onlyonce=0;
                ridup=ridup->next;
                }
        struct entityOrRelationIndex *t;
        t=eorihead;
        while(t!=NULL)
                {
                if(!strcmp(t->name,weakentityname))
                        t->eorrflag=0;
                t=t->next;
                }
        }

void displayStructures()
	{
	eoritemp=eorihead;
	while(eoritemp!=NULL)
		{
		printf("\nIn struct  %s type %d\n",eoritemp->name,eoritemp->eorrflag);
		abtemp=eoritemp->link;
		while(abtemp!=NULL)
			{
			printf("\tattributes %s\n",abtemp->name);
			abtemp=abtemp->next;
			}	
		eoritemp=eoritemp->next;
		}
	ritemp=rihead;
	while(ritemp!=NULL)
		{
		printf("\nIN relation %s nary %d identify%d weakcount %d\n",ritemp->name,ritemp->n_ary
		,ritemp->identifyflag,ritemp->weakentityexists);
		eirbtemp=ritemp->link;
		while(eirbtemp!=NULL)
			{
			printf("\tEntities= %s fulldependent=%d weak=%d arity=%d\n",eirbtemp->name
				,eirbtemp->fulldependent,eirbtemp->weak,eirbtemp->arity);
			abtemp=eirbtemp->bucketlink;
			while(abtemp!=NULL)
				{
				printf("\t\tattributes %s\n",abtemp->name);
				abtemp=abtemp->next;
				}
			eirbtemp=eirbtemp->next;
			}
		ritemp=ritemp->next;
		}
	}

void checklengthpreceision(char *name,int length,int precision)
	{
	if(length<=precision)
		{
		printf("\nIn %s data type the length %d cant be less than precision %d check it out\n\n"
		,name,length,precision);
		exit(0);
		}
	else
		return;
	}
