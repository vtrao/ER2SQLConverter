
	CREATE DATABASE interviewer ;

	USE interviewer ;

	CREATE TABLE  candidate  ( 
		name VARCHAR(6), 
		PRIMARY KEY (name ) );

	CREATE TABLE  company  ( 
		cname VARCHAR(6), 
		PRIMARY KEY (cname ) );

	CREATE TABLE  joboffer  ( 
		results INTEGER, 
		PRIMARY KEY (results ) );

	CREATE TABLE  interview ( 
		dept INTEGER,
		dat INTEGER,
		name_1 VARCHAR(6),
		cname_1 VARCHAR(6),
		PRIMARY KEY (   name_1 ,  cname_1 , dept , dat  ),
		FOREIGN KEY ( name_1) REFERENCES  candidate (name) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( cname_1) REFERENCES  company (cname) ON DELETE CASCADE ON UPDATE CASCADE  );

	ALTER TABLE joboffer 
		ADD COLUMN ( dept_2 INTEGER ),
		ADD COLUMN ( dat_2 INTEGER ),
		ADD COLUMN ( name_1_2 VARCHAR(6) ),
		ADD COLUMN ( cname_1_2 VARCHAR(6) ),
		ADD FOREIGN KEY ( dept_2) REFERENCES  interview (dept) ON DELETE CASCADE ON UPDATE CASCADE,
		ADD FOREIGN KEY ( dat_2) REFERENCES  interview (dat) ON DELETE CASCADE ON UPDATE CASCADE,
		ADD FOREIGN KEY ( name_1_2) REFERENCES  interview (name_1) ON DELETE CASCADE ON UPDATE CASCADE,
		ADD FOREIGN KEY ( cname_1_2) REFERENCES  interview (cname_1) ON DELETE CASCADE ON UPDATE CASCADE ;

	CREATE TABLE cci_table ( 
		cnamefk VARCHAR(6),
		PRIMARY KEY (  cnamefk ),
		FOREIGN KEY ( namefk) REFERENCES  candidate (name) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( cnamefk) REFERENCES  company (cname) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( deptfk) REFERENCES  interview (dept) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( datfk) REFERENCES  interview (dat) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( name_1fk) REFERENCES  interview (name_1) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( cname_1fk) REFERENCES  interview (cname_1) ON DELETE CASCADE ON UPDATE CASCADE  );
