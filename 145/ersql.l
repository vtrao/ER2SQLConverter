%{
   #include "ersql.tab.h"
   #include<stdio.h>
	
%}

%%

\/\*([^*]|\*[^/])*\*\/(\n*)   { }

(\/\/|(\/\/[\/]+))(.*)	      { }	

(\"(.)*\")		      { }

("vaavs")                 { yylval = (int)strdup(yytext);       return vaavs;       }

("struct")                { yylval = (int)strdup(yytext);       return strut;       }

("weakentitytype")        { yylval = (int)strdup(yytext);       return wken;        }

("entitytype")            { yylval = (int)strdup(yytext);       return en;          }

("relationtype")          { yylval = (int)strdup(yytext);       return rn;          }

("pkey")                  { yylval = (int)strdup(yytext);       return pk;          }

("mulv")                  { yylval = (int)strdup(yytext);       return mulv;        }

("partialkey")	          { yylval = (int)strdup(yytext);       return partialkey;  } 

("notnull")		  { yylval = (int)strdup(yytext);       return notnull;     }

("database")              { yylval = (int)strdup(yytext);       return dbname;      }

("unique")		  { yylval = (int)strdup(yytext);	return uni;         }

("relation")              { yylval = (int)strdup(yytext);       return relation;    }     

("totpart")               { yylval = (int)strdup(yytext);       return fd;          }			

("identify")	          { yylval = (int)strdup(yytext);       return identify;    }	

("integer")               { yylval = (int)strdup(yytext);       return   integer;   }

("smallint")              { yylval = (int)strdup(yytext);       return   smallint;  }

("number")                { yylval = (int)strdup(yytext);       return   number;    }

("decimal")               { yylval = (int)strdup(yytext);       return   decimal;   }

("double")                { yylval = (int)strdup(yytext);       return   doub;      }

("float")                 { yylval = (int)strdup(yytext);       return   floa;      }

("char")                  { yylval = (int)strdup(yytext);       return   cha;       }

("varchar")               { yylval = (int)strdup(yytext);       return   varchar;   }

("date")                  { yylval = (int)strdup(yytext);       return   dat;       }

("datetime")              { yylval = (int)strdup(yytext);       return   dattim;    }

("timestamp")             { yylval = (int)strdup(yytext);       return   timestamp; }

(";")                     { yylval = (int)strdup(yytext);       return semicolon;   }

("{")                     { yylval = (int)strdup(yytext);       return curbrop;     }

("}")                     { yylval = (int)strdup(yytext);       return curbrcl;     }

("[")                     { yylval = (int)strdup(yytext);       return sqbrop;      }

("]")                     { yylval = (int)strdup(yytext);       return sqbrcl;      }

[0-9]*                    { yylval = (int)strdup(yytext);       return num;         }

[a-zA-Z_$][a-zA-Z_0-9]*   { yylval = (int)strdup(yytext);       return id;          }

("\b")                    { }

(" ")			  { }

("\t")                    { }

("\n")                    { } 

("\f")                    { }

("\r")                    { }

("-")			  { }

.|\n                      { }

%%

