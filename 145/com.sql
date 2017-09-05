
	CREATE DATABASE company ;

	USE company ;

	CREATE TABLE  employee  ( 
		ssn INTEGER,
		bdate INTEGER,
		name VARCHAR(10),
		salary INTEGER,
		sex INTEGER, 
		PRIMARY KEY (ssn ) );

	CREATE TABLE  department  ( 
		name VARCHAR(5),
		dnumber NUMERIC(4,3), 
		PRIMARY KEY (dnumber ) );

	CREATE TABLE  project  ( 
		name VARCHAR(5),
		pnumbe VARCHAR(6),
		location VARCHAR(5), 
		PRIMARY KEY (pnumbe ) );

	CREATE TABLE  dependant ( 
		name VARCHAR(5),
		sex NUMERIC(6,3),
		birthdate INTEGER,
		ssn_1 INTEGER,
		PRIMARY KEY (   ssn_1 , name  ),
		FOREIGN KEY ( ssn_1) REFERENCES  employee (ssn) ON DELETE CASCADE ON UPDATE CASCADE  );

	ALTER TABLE department 
		ADD COLUMN ( ssn_2 INTEGER ),
		ADD COLUMN ( startdate INTEGER ),
		ADD FOREIGN KEY ( ssn_2) REFERENCES  employee (ssn) ON DELETE CASCADE ON UPDATE CASCADE ;

	ALTER TABLE employee 
		ADD COLUMN (  ssn_3 INTEGER ),
		ADD FOREIGN KEY ( ssn_3) REFERENCES  employee (ssn)  ON DELETE CASCADE ON UPDATE CASCADE ;

	ALTER TABLE department 
		ADD COLUMN (  ssn_4 INTEGER ),
		ADD FOREIGN KEY ( ssn_4) REFERENCES  employee (ssn)  ON DELETE CASCADE ON UPDATE CASCADE ;

	ALTER TABLE department 
		ADD COLUMN (  pnumbe_5 VARCHAR(6) ),
		ADD FOREIGN KEY ( pnumbe_5) REFERENCES  project (pnumbe)  ON DELETE CASCADE ON UPDATE CASCADE ;

	CREATE TABLE works_on_table ( 
		ssnfk INTEGER,
		hours NUMERIC(7,3),
		pnumbefk VARCHAR(6),
		PRIMARY KEY (  ssnfk, pnumbefk ),
		FOREIGN KEY ( ssnfk) REFERENCES  employee (ssn) ON DELETE CASCADE ON UPDATE CASCADE ,
		FOREIGN KEY ( pnumbefk) REFERENCES  project (pnumbe) ON DELETE CASCADE ON UPDATE CASCADE  );

	CREATE TABLE department_locations ( 
		locations VARCHAR(5),
		dnumberfk NUMERIC(4,3),
		PRIMARY KEY (  dnumberfk  ),
		FOREIGN KEY (dnumberfk) REFERENCES department(dnumber) ON DELETE CASCADE ON UPDATE CASCADE  );
