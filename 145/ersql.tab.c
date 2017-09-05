/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     vaavs = 258,
     sqbrop = 259,
     sqbrcl = 260,
     strut = 261,
     id = 262,
     en = 263,
     rn = 264,
     curbrop = 265,
     curbrcl = 266,
     pk = 267,
     num = 268,
     notnull = 269,
     uni = 270,
     relation = 271,
     semicolon = 272,
     fd = 273,
     dbname = 274,
     mulv = 275,
     identify = 276,
     integer = 277,
     smallint = 278,
     number = 279,
     decimal = 280,
     wken = 281,
     doub = 282,
     floa = 283,
     cha = 284,
     varchar = 285,
     dat = 286,
     partialkey = 287,
     dattim = 288,
     timestamp = 289,
     linecounter = 290
   };
#endif
#define vaavs 258
#define sqbrop 259
#define sqbrcl 260
#define strut 261
#define id 262
#define en 263
#define rn 264
#define curbrop 265
#define curbrcl 266
#define pk 267
#define num 268
#define notnull 269
#define uni 270
#define relation 271
#define semicolon 272
#define fd 273
#define dbname 274
#define mulv 275
#define identify 276
#define integer 277
#define smallint 278
#define number 279
#define decimal 280
#define wken 281
#define doub 282
#define floa 283
#define cha 284
#define varchar 285
#define dat 286
#define partialkey 287
#define dattim 288
#define timestamp 289
#define linecounter 290




/* Copy the first part of user declarations.  */
#line 2 "ersql.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 230 "ersql.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  17
/* YYNRULES -- Number of rules. */
#define YYNRULES  59
/* YYNRULES -- Number of states. */
#define YYNSTATES  115

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    17,    19,    23,
      25,    28,    35,    42,    49,    51,    54,    58,    63,    68,
      73,    75,    78,    82,    88,    94,    99,   104,   106,   109,
     114,   119,   125,   131,   135,   140,   146,   152,   157,   159,
     162,   169,   175,   177,   180,   185,   190,   194,   198,   201,
     203,   205,   209,   211,   215,   217,   220,   223,   225,   227
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      37,     0,    -1,    -1,     3,     4,    38,     5,    -1,    -1,
      39,    40,    48,    -1,    39,    40,    -1,    39,    -1,    19,
       7,    17,    -1,    41,    -1,    40,    41,    -1,     6,     7,
       8,    10,    46,    11,    -1,     6,     7,     9,    10,    44,
      11,    -1,     6,     7,    26,    10,    42,    11,    -1,    43,
      -1,    42,    43,    -1,     7,    52,    17,    -1,     7,    52,
      32,    17,    -1,     7,    52,    14,    17,    -1,     7,    52,
      20,    17,    -1,    45,    -1,    44,    45,    -1,     7,    52,
      17,    -1,     7,    52,    14,    15,    17,    -1,     7,    52,
      15,    14,    17,    -1,     7,    52,    15,    17,    -1,     7,
      52,    14,    17,    -1,    47,    -1,    46,    47,    -1,     7,
      52,    12,    17,    -1,     7,    52,    15,    17,    -1,     7,
      52,    14,    15,    17,    -1,     7,    52,    15,    14,    17,
      -1,     7,    52,    17,    -1,     7,    52,    14,    17,    -1,
       7,    52,    20,    14,    17,    -1,     7,    52,    14,    20,
      17,    -1,     7,    52,    20,    17,    -1,    49,    -1,    48,
      49,    -1,    16,     7,    21,    10,    50,    11,    -1,    16,
       7,    10,    50,    11,    -1,    51,    -1,    50,    51,    -1,
       7,    18,    13,    17,    -1,     7,    13,    18,    17,    -1,
       7,    13,    17,    -1,     7,    18,    17,    -1,     7,    17,
      -1,    22,    -1,    23,    -1,    24,    13,    13,    -1,    25,
      -1,    27,    13,    13,    -1,    28,    -1,    29,    13,    -1,
      30,    13,    -1,    31,    -1,    33,    -1,    34,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    95,    95,    96,    99,   100,   101,   104,   107,   110,
     111,   114,   115,   116,   119,   120,   123,   124,   125,   126,
     129,   130,   133,   134,   135,   136,   137,   140,   141,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   155,   156,
     159,   160,   163,   164,   167,   168,   169,   170,   171,   176,
     177,   178,   180,   181,   183,   184,   185,   186,   187,   188
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "vaavs", "sqbrop", "sqbrcl", "strut", "id", 
  "en", "rn", "curbrop", "curbrcl", "pk", "num", "notnull", "uni", 
  "relation", "semicolon", "fd", "dbname", "mulv", "identify", "integer", 
  "smallint", "number", "decimal", "wken", "doub", "floa", "cha", 
  "varchar", "dat", "partialkey", "dattim", "timestamp", "linecounter", 
  "$accept", "S", "STMTS", "DBSTMT", "STDEFS", "STDEF", "DECLWKS", 
  "DECLWK", "DECLSRAS", "DECLSRA", "DECLS", "DECL", "REDEFS", "REDEF", 
  "RSTMTS", "RSTMT", "TYPE", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    39,    40,
      40,    41,    41,    41,    42,    42,    43,    43,    43,    43,
      44,    44,    45,    45,    45,    45,    45,    46,    46,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    51,    51,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     1,     3,     1,
       2,     6,     6,     6,     1,     2,     3,     4,     4,     4,
       1,     2,     3,     5,     5,     4,     4,     1,     2,     4,
       4,     5,     5,     3,     4,     5,     5,     4,     1,     2,
       6,     5,     1,     2,     4,     4,     3,     3,     2,     1,
       1,     3,     1,     3,     1,     2,     2,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     0,     4,     1,     0,     0,     7,     0,     3,
       0,     6,     9,     8,     0,     0,    10,     5,    38,     0,
       0,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,    20,     0,     0,    14,     0,     0,
      42,     0,    49,    50,     0,    52,     0,    54,     0,     0,
      57,    58,     0,     0,    11,    28,     0,    12,    21,     0,
      13,    15,     0,    48,     0,    41,    43,     0,     0,     0,
      55,    56,    59,     0,     0,     0,    33,     0,     0,     0,
      22,     0,    16,     0,     0,    46,     0,     0,    47,    40,
      51,    53,    29,     0,    34,     0,     0,    30,     0,    37,
       0,    26,     0,    25,    18,    19,    17,    45,    44,    31,
      36,    32,    35,    23,    24
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     6,     7,    11,    12,    36,    37,    33,    34,
      30,    31,    17,    18,    39,    40,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yysigned_char yypact[] =
{
      19,     4,    23,    33,   -40,    47,    51,    62,    52,   -40,
      63,     5,   -40,   -40,    -6,    64,   -40,    56,   -40,    65,
      66,    67,    -5,   -40,    71,    72,    73,    74,    75,     2,
      30,   -40,     2,    36,   -40,     2,    37,   -40,    21,    39,
     -40,    74,   -40,   -40,    60,   -40,    61,   -40,    69,    70,
     -40,   -40,    76,    -2,   -40,   -40,    43,   -40,   -40,   -13,
     -40,   -40,    49,   -40,    38,   -40,   -40,    42,    77,    78,
     -40,   -40,   -40,    79,    25,    -8,   -40,     0,    48,    45,
     -40,    80,   -40,    81,    82,   -40,    83,    84,   -40,   -40,
     -40,   -40,   -40,    85,   -40,    86,    87,   -40,    88,   -40,
      89,   -40,    90,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -40,   -40,   -40,   -40,   -40,    97,   -40,    50,   -40,    54,
     -40,    58,   -40,    92,    53,   -39,    29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      66,    81,    19,    20,    82,    27,    96,    83,     3,    97,
      73,    10,    74,    75,    98,    76,    28,    99,    77,    84,
      21,    15,     1,     4,    42,    43,    44,    45,    66,    46,
      47,    48,    49,    50,    62,    51,    52,    29,    63,    64,
      93,    54,    94,    32,    35,    95,    38,    57,    60,    38,
      65,    87,     5,    89,     8,    88,     9,    78,    79,   102,
      80,    56,   103,   100,    59,   101,    85,    86,    10,    13,
      14,    22,    15,    68,    69,    24,    25,    26,    29,    32,
      35,    38,    70,    71,     0,    41,    61,    58,    55,    72,
      90,    91,     0,     0,    67,     0,    92,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    16,    23
};

static const yysigned_char yycheck[] =
{
      39,    14,     8,     9,    17,    10,    14,    20,     4,    17,
      12,     6,    14,    15,    14,    17,    21,    17,    20,    32,
      26,    16,     3,     0,    22,    23,    24,    25,    67,    27,
      28,    29,    30,    31,    13,    33,    34,     7,    17,    18,
      15,    11,    17,     7,     7,    20,     7,    11,    11,     7,
      11,    13,    19,    11,     7,    17,     5,    14,    15,    14,
      17,    32,    17,    15,    35,    17,    17,    18,     6,    17,
       7,     7,    16,    13,    13,    10,    10,    10,     7,     7,
       7,     7,    13,    13,    -1,    10,    36,    33,    30,    13,
      13,    13,    -1,    -1,    41,    -1,    17,    17,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,    11,    17
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,    37,     4,     0,    19,    38,    39,     7,     5,
       6,    40,    41,    17,     7,    16,    41,    48,    49,     8,
       9,    26,     7,    49,    10,    10,    10,    10,    21,     7,
      46,    47,     7,    44,    45,     7,    42,    43,     7,    50,
      51,    10,    22,    23,    24,    25,    27,    28,    29,    30,
      31,    33,    34,    52,    11,    47,    52,    11,    45,    52,
      11,    43,    13,    17,    18,    11,    51,    50,    13,    13,
      13,    13,    13,    12,    14,    15,    17,    20,    14,    15,
      17,    14,    17,    20,    32,    17,    18,    13,    17,    11,
      13,    13,    17,    15,    17,    20,    14,    17,    14,    17,
      15,    17,    14,    17,    17,    17,    17,    17,    17,    17,
      17,    17,    17,    17,    17
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 107 "ersql.y"
    { strcpy(databasename,(char *)yyvsp[-1]); ;}
    break;

  case 11:
#line 114 "ersql.y"
    {createHashIndexStructDef((char *)yyvsp[-4],0);;}
    break;

  case 12:
#line 115 "ersql.y"
    {createHashIndexStructDef((char *)yyvsp[-4],1);;}
    break;

  case 13:
#line 116 "ersql.y"
    {createHashIndexStructDef((char *)yyvsp[-4],2);;}
    break;

  case 16:
#line 123 "ersql.y"
    {fillList((char *)yyvsp[-2],0,0,0,0,0);;}
    break;

  case 17:
#line 124 "ersql.y"
    {fillList((char *)yyvsp[-3],0,0,0,0,1);;}
    break;

  case 18:
#line 125 "ersql.y"
    {fillList((char *)yyvsp[-3],0,1,0,0,0);;}
    break;

  case 19:
#line 126 "ersql.y"
    {fillList((char *)yyvsp[-3],0,0,0,1,0);;}
    break;

  case 22:
#line 133 "ersql.y"
    {fillList((char *)yyvsp[-2],0,0,0,0,0);;}
    break;

  case 23:
#line 134 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,1,0,0);;}
    break;

  case 24:
#line 135 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,1,0,0);;}
    break;

  case 25:
#line 136 "ersql.y"
    {fillList((char *)yyvsp[-3],0,0,1,0,0);;}
    break;

  case 26:
#line 137 "ersql.y"
    {fillList((char *)yyvsp[-3],0,1,0,0,0);;}
    break;

  case 29:
#line 144 "ersql.y"
    {fillList((char *)yyvsp[-3],1,0,0,0,0);;}
    break;

  case 30:
#line 145 "ersql.y"
    {fillList((char *)yyvsp[-3],0,0,1,0,0);;}
    break;

  case 31:
#line 146 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,1,0,0);;}
    break;

  case 32:
#line 147 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,1,0,0);;}
    break;

  case 33:
#line 148 "ersql.y"
    {fillList((char *)yyvsp[-2],0,0,0,0,0);;}
    break;

  case 34:
#line 149 "ersql.y"
    {fillList((char *)yyvsp[-3],0,1,0,0,0);;}
    break;

  case 35:
#line 150 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,0,1,0);;}
    break;

  case 36:
#line 151 "ersql.y"
    {fillList((char *)yyvsp[-4],0,1,0,1,0);;}
    break;

  case 37:
#line 152 "ersql.y"
    {fillList((char *)yyvsp[-3],0,0,0,1,0);;}
    break;

  case 40:
#line 159 "ersql.y"
    {createHashIndexRelation((char *)yyvsp[-4],1);;}
    break;

  case 41:
#line 160 "ersql.y"
    {createHashIndexRelation((char *)yyvsp[-3],0);;}
    break;

  case 44:
#line 167 "ersql.y"
    {createEntityList((char *)yyvsp[-3],1,atoi(yyvsp[-1]));;}
    break;

  case 45:
#line 168 "ersql.y"
    {createEntityList((char *)yyvsp[-3],1,atoi(yyvsp[-2]));;}
    break;

  case 46:
#line 169 "ersql.y"
    {createEntityList((char *)yyvsp[-2],0,atoi(yyvsp[-1]));;}
    break;

  case 47:
#line 170 "ersql.y"
    {createEntityList((char *)yyvsp[-2],1,0);       ;}
    break;

  case 48:
#line 171 "ersql.y"
    {createEntityList((char *)yyvsp[-1],0,0);       ;}
    break;

  case 49:
#line 176 "ersql.y"
    {createList(1,0,0);;}
    break;

  case 50:
#line 177 "ersql.y"
    {createList(2,0,0);;}
    break;

  case 51:
#line 178 "ersql.y"
    {checklengthpreceision((char *)yyvsp[-2],atoi(yyvsp[-1]),atoi(yyvsp[0]));
						createList(3,atoi(yyvsp[-1]),atoi(yyvsp[0]));;}
    break;

  case 52:
#line 180 "ersql.y"
    {createList(4,0,0);;}
    break;

  case 53:
#line 181 "ersql.y"
    {checklengthpreceision((char *)yyvsp[-2],atoi(yyvsp[-1]),atoi(yyvsp[0]));
					createList(5,atoi(yyvsp[-1]),atoi(yyvsp[0]));;}
    break;

  case 54:
#line 183 "ersql.y"
    {createList(6,0,0);;}
    break;

  case 55:
#line 184 "ersql.y"
    {createList(7,0,atoi(yyvsp[0]));;}
    break;

  case 56:
#line 185 "ersql.y"
    {createList(8,0,atoi(yyvsp[0]));;}
    break;

  case 57:
#line 186 "ersql.y"
    {createList(9,0,0);;}
    break;

  case 58:
#line 187 "ersql.y"
    {createList(10,0,0);;}
    break;

  case 59:
#line 188 "ersql.y"
    {createList(11,0,atoi(yyvsp[0]));;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1402 "ersql.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__) \
    && !defined __cplusplus
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 190 "ersql.y"


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

