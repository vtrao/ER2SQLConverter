import java.awt.*;
import java.io.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.text.*;
import javax.swing.event.*;
import javax.swing.undo.*;
import javax.swing.text.*;
import javax.swing.KeyStroke.*;
import java.awt.Color;
import java.lang.*;

/** THIS PROGRAM IS AN ER TO QUERY CONVERTER
 *  @author Shashank*/

public class editor extends JFrame implements ActionListener
{
 Container c1,c,c2 ;//= new JPanel();
 JPanel jp = new JPanel();
 JTabbedPane tabs = new JTabbedPane();
 JMenuBar mb;
 JMenu m1,m2,m4,m5,m6;
 JMenuItem m1i1,m1i2,m1i3,m1i4,m1i5,m1i6,m1i7,m1i8,m1i9;
 JMenuItem m2i1,m2i2,m2i3,m2i4,m2i5,m2i6,m2i7,m2i9,m2i10,m2i11,m2i12,m2i13,exeinsql;
 //MenuItem m3i1,m3i2;
 JMenuItem m4i1,m4i2;
 JMenuItem m5i1;
 JMenuItem m6i1,m6i2,m6i3;
 CheckboxMenuItem m2i8;
 UIManager.LookAndFeelInfo xx[];
 JTextArea ta;
 String s="",s1,str,str1;
 String input="";
 String syntax="Capitalized words are user defined words(follows  a valid 'c' identifier)\n"+
"Small words are keywords(Refer to the keynotes for further details on keywords)\n"+
"/-Specifies any one of the options can be used               (...)- Specifies optional statements\n"+
" vaavs \n"+
"[\n"+
"struct ENTITYNAME entitytype\n"+
"     {\n"+
"     ATTRIBUTENAME type (pkey)(notnull)(unique)(mulv) ;\n"+
"     ............\n"+
"     //one primary key is compulsary,"+
"No partial keys allowed,"+
"Multivalued attribute cannot be primary key\n"+
"     }\n"+
"............\n"+
"struct WEAKENTITYNAME weakentitytype\n"+
"     { \n"+
"     ATTRIBUTENAME type  (partialkey)/(notnull)/(mulv);\n"+
"     ............\n"+
"     //Partial Key is not compulsary,"+
"No primary key allowed\n"+
"     }\n"+
"............\n"+
"struct RELATIONAME relationtype\n"+
"     {\n"+
"     ATTRIBUTENAME  type (notnull)(uni)  ;\n"+
"     //No primary key or partial key allowed\n"+
"     ............\n"+
"     }\n"+
"............\n"+
"// No need of particular order for structure defination, "+
"All valid C comments are allowed\n"+
"relation RELATIONSHIPNAME (identify)\n"+
"     {\n"+
"     ENTITYNAME (totpart) num ; \n"+
"     WEAKENTITYNAME (totpart) num;\n"+
"     ............\n"+
"     //Atleast 2 entities to be declared, "+
"In case of recursive the entity name can be repeated\n"+
"     }\n"+
"............\n"+ 
"]";
String msg="";
 File f1,f2,f3;
 MenuShortcut msc;
 int flag=0,v,h;
 int x,y,i=0;
 File f;
 FileOutputStream fos;
 FileInputStream fis;
 byte b[]=new byte[20];
 String line="";
 DateFormat df,df1;
 Date d;
 JScrollPane jsp,outLabel1,mysql1;
  int fileflag=0;
//JLabel editorWindow = new JLabel("This is Editor Window");
 //JLabel outputWindow = new JLabel("This is Output Window");
String filename;
JTextArea outLabel = new JTextArea("",20,80);
JTextArea mysql  = new JTextArea("",20,80);
 private UndoManager undo = new UndoManager();
String Completepath;
 editor()
 {
  try
  {
 
 xx=UIManager.getInstalledLookAndFeels();
        UIManager.setLookAndFeel(xx[1].getClassName());}catch(Exception q){}
  MyWindowAdapter adapter=new MyWindowAdapter(this);
  addWindowListener(adapter);
  ta= new JTextArea("",20,80);
  jsp=new JScrollPane(ta);
  outLabel1=new JScrollPane(outLabel);
  mysql1 =  new JScrollPane(mysql);
  tabs.add("Editor",jsp);
  tabs.add("Output",outLabel1);
  tabs.add("MySQL",mysql1);
  tabs.addChangeListener(new ChangeListener()
   {
	public void stateChanged(ChangeEvent e)
	{
		System.out.println(tabs.getSelectedIndex());
	}
   });
   c = getContentPane();
   c.add(tabs);
  tabs.setEnabledAt(1,false);
  tabs.setEnabledAt(2,false);
  setTitle("VAAVS-ER TO QUERY GENERATOR");
  msc=new MenuShortcut(79);
  mb=new JMenuBar();
  m1=new JMenu("File");
  m1.setMnemonic('F');
  m2=new JMenu("Edit");
   m2.setMnemonic('D');
  //m3=new Menu("Search");
  m4=new JMenu("Info");
   m4.setMnemonic('I');
  m5=new JMenu("Execute");
   m5.setMnemonic('E');
  m6=new JMenu("Help");
   m6.setMnemonic('H');

  m1i1=new JMenuItem("New");
   m1i1.setMnemonic('N');
  m1i2=new JMenuItem("Open");
    m1i2.setMnemonic('O');
  m1i8=new JMenuItem("-");
  m1i9=new JMenuItem("-");
  m1i3=new JMenuItem("Save");
   m1i3.setMnemonic('S');
  m1i4=new JMenuItem("Save As..");
   m1i4.setMnemonic('A');
  m1i5=new JMenuItem("Page Setup");
  m1i6=new JMenuItem("Print");
  m1i7=new JMenuItem("Exit");
   m1i7.setMnemonic('X');
  m1.add(m1i1); m1.add(m1i2); m1.add(m1i3); m1.add(m1i4);//m1.add(m1i8);m1.add(m1i5);m1.add(m1i6); m1.add(m1i9);
  m1.add(m1i7);


  m2i10=new JMenuItem("-");
  m2i11=new JMenuItem("-");
  m2i12=new JMenuItem("-");
  m2i1=new JMenuItem("Undo");
   m2i1.setMnemonic('U');
  m2i13=new JMenuItem("Redo");
    m2i13.setMnemonic('R');
  m2i2=new JMenuItem("Cut");
    //m2i2.setMnemonic('C');
   m2i2.setMnemonic('T'); 
m2i3=new JMenuItem("Copy");
     m2i3.setMnemonic('Y');
  m2i4=new JMenuItem("Paste");
     m2i4.setMnemonic('P');
  m2i5=new JMenuItem("Delete");
	m2i5.setMnemonic('L'); 
 m2i6=new JMenuItem("Select All");
   m2i6.setMnemonic('C'); 
 m2i7=new JMenuItem("Time/Date F5");
  m2i8=new CheckboxMenuItem("WordWrap");
  m2i9=new JMenuItem("Set Font...");
   m2.add(m2i1); m2.add(m2i13);m2.add(m2i2); m2.add(m2i3); m2.add(m2i4); m2.add(m2i5);m2.add(m2i6);//m2.add(m2i7);//m2.add(m2i8);m2.add(m2i9); m2.add(m2i10);m2.add(m2i11);m2.add(m2i12);

  m4i1=new JMenuItem("Know VAAVS Developers");
   m4i1.setMnemonic('W');
  m4i2=new JMenuItem("About VERSION");
   m2i2.setMnemonic('V');
  m4.add(m4i1); m4.add(m4i2);

  m5i1=new JMenuItem("Build");
   m5i1.setMnemonic('B');
  exeinsql = new JMenuItem("Execute in MYSQL");
   exeinsql.setMnemonic('M');	
  m5.add(m5i1);
  m5.add(exeinsql);
	

  m6i1=new JMenuItem("Show Syntax");
   m6i1.setMnemonic('Y');
  m6i2=new JMenuItem("KeyNotes");
   m6i2.setMnemonic('K');
m6i3=new JMenuItem("Data Types");  
m6.add(m6i1);
  m6.add(m6i2);
m6.add(m6i3);
  mb.add(m1);mb.add(m2);//mb.add(m3);
  mb.add(m5);mb.add(m6);mb.add(m4);
  setJMenuBar(mb);

  m1i1.addActionListener(this);
  m1i2.addActionListener(this);
  m1i3.addActionListener(this);
  m1i4.addActionListener(this);
  m1i7.addActionListener(this);

  m2i1.addActionListener(this);
  m2i13.addActionListener(this);
  m2i2.addActionListener(this);
  m2i3.addActionListener(this);
  m2i4.addActionListener(this);
  m2i5.addActionListener(this);
  m2i6.addActionListener(this);
  m2i7.addActionListener(this);
  m2i8.addActionListener(this);
  m2i9.addActionListener(this);

  m4i1.addActionListener(this);
  m4i2.addActionListener(this);

  m5i1.addActionListener(this);
  exeinsql.addActionListener(this);	
  m6i1.addActionListener(this);
  m6i2.addActionListener(this);
  m6i3.addActionListener(this);
  mysql.setEditable(false);
    Document doc = ta.getDocument();
    doc.addUndoableEditListener(new UndoableEditListener() {
    public void undoableEditHappened(UndoableEditEvent evt) {
    undo.addEdit(evt.getEdit());
  }
  });
  ta.setWrapStyleWord(false);
  outLabel.setEditable(false);
  setSize(1000,1000);
  setVisible(true);
  }
	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
        this.setSize(170, 80);
			
	}
    public String getExtension(String  f) {
        if(f != null) {
            int extensionIndex = f.lastIndexOf('.');
	    if(extensionIndex < 0) {
		return null;
	    }
            return f.substring(extensionIndex+1).toLowerCase();
	}
	return null;
    }
  public void actionPerformed(ActionEvent ae)
  {
    if(ae.getSource()==m1i2)
    {
     FileDialog fd=new FileDialog(this,"Open",FileDialog.LOAD);
     fd.setVisible(true);
     s=fd.getFile();
     setTitle(s+"- SAVED E-R DATA MODEL IN VAAVS");
     str=fd.getDirectory();
     str1=(fd.getDirectory()+fd.getFile());
     input = str1;	
     s1=getExtension(s);

     try
     {
      ta.setText("");
      FileReader fr=new FileReader(str1);
      BufferedReader br=new BufferedReader(fr);
      while((line=br.readLine())!=null)
      {
       ta.append(line+"\n");
      }
     }
     catch(Exception e){}
	tabs.setSelectedIndex(0);
    }
    if(ae.getSource()==m1i3)
    {
     DataInputStream dis;
     try
     {
      if(fileflag==0)
      {
     FileDialog fd=new FileDialog(this,"Save",FileDialog.SAVE);
     fd.setVisible(true);
     s=fd.getFile();
     filename=s;
     str1=fd.getDirectory()+fd.getFile();
     input = str1;	
     setTitle(s+"- SAVED E-R DATA MODEL IN VAAVS");
     System.out.println(filename);
     fileflag=1;
     }
     s1="";
     s1=ta.getText();
     FileWriter fw=new FileWriter(filename);
     StringReader sr=new  StringReader(s1);
     BufferedReader br=new BufferedReader(sr);
     String lr="";
     while((lr=br.readLine())!=null)
     {
      fw.write(lr+"\r\n");
     }
      fw.close();
       }catch(Exception pe){setTitle("UNTITLED.txt");}
	tabs.setSelectedIndex(0);
     }
    if(ae.getSource()==m1i4)
    {
     FileDialog fd=new FileDialog(this,"Save As",FileDialog.SAVE);
     fd.setVisible(true);
     s=fd.getFile();
     filename=s;
     setTitle(s+" - NOTEPAD");
      DataInputStream dis;
     str1=fd.getDirectory()+fd.getFile();
     input = str1;	
      try
      {
     s1="";
     s1=ta.getText();
     FileWriter fw=new FileWriter(filename);
     StringReader sr=new  StringReader(s1);
     BufferedReader br=new BufferedReader(sr);
     String lr="";
     while((lr=br.readLine())!=null)
     {
      fw.write(lr+"\r\n");
     }
      fw.close();

       fileflag=1;
       }catch(Exception pe){}
	tabs.setSelectedIndex(0);
    }
    if(ae.getSource()==m1i7)
    {
     System.exit(0);
    }
    if(ae.getSource()==m1i1)
    {
     s="";
    ta.setText(s);
    setTitle("UNTITLED-VAAVS E-R TO QUERY CONVERTER");
	fileflag=0;
	filename="";

    }
    if(ae.getSource()==m2i1)
    {
        try {
              if (undo.canUndo())
              {
              undo.undo();
           }
      } catch (CannotUndoException e) {   }
    }
    if(ae.getSource()==m2i9)
    {

          myfont  myfon=new myfont(this);
    }
  if(ae.getSource()==m2i13)
    {
     try {
           if (undo.canRedo())
            {
             undo.redo();
          }
   } catch (CannotRedoException e) { }
  }
    if(ae.getSource()==m2i2)
    {
     s=ta.getSelectedText();
     ta.cut();
    }
    /*if(ae.getSource()==m3i2)
    {

search sear=new search(this);
    }*/

    if(ae.getSource()==m2i3)
    {
     s=ta.getSelectedText();
     ta.copy();
    }
    if(ae.getSource()==m2i4)
    {
     s=ta.getSelectedText();
     ta.paste();
    }
    if(ae.getSource()==m2i6)
    {
     ta.selectAll();
    }

    if(ae.getSource()==m2i5)
    {
     x=ta.getSelectionStart();
     y=ta.getSelectionEnd();
     ta.replaceRange(" ",x,y);
   }
    if(ae.getSource()==m2i8)
    {
      if(ta.getWrapStyleWord()==false)
      {
     ta.setWrapStyleWord(true);
     System.out.println("wordwrap is set");
     }
     else
     {
      ta.setWrapStyleWord(false);
      System.out.println("wordwrap is not set");
    }
   }
   if(ae.getSource()==m2i7)
   {
    d=new Date();
         df=DateFormat.getDateInstance(DateFormat.MEDIUM);
         df1=DateFormat.getTimeInstance(DateFormat.MEDIUM);

    str= df.format(d);
    str1=df1.format(d);

    ta.setText(str+"   "+str1);
   }
   /*if(ae.getSource()==m3i1)
   {
    search sear=new search(this);
   }*/
   if(ae.getSource()==m4i1)
   {

  
    JOptionPane.showMessageDialog(null,"Developed by\n\tV     Venkat Naidu          2005-145 IIITB     "+ 				   "\n\tA     Abhinav Meherotra  2005-004 IIITB        "+
        "\n\tA     Abhijeeth Rao         2005-002 IIITB   "+
	"\n\tV     Vikram Jain             2005-151 IIITB "+
	"\n\tS      Shashank Handa     2005-117 IIITB     ","",JOptionPane.INFORMATION_MESSAGE);
    
   }
   if(ae.getSource()==m4i2)
   {
    s="This program is developed by VASAV,IIITB ";
    //help2 hel=new help();
    JOptionPane.showMessageDialog(null,"Version 1.0 ","",JOptionPane.INFORMATION_MESSAGE);
   
   }
if(ae.getSource()==m5i1)
   {
	if(input.length() < 1)
	{
	JOptionPane.showMessageDialog(null,"Please save the File before executing","",JOptionPane.INFORMATION_MESSAGE);	
	}
	else
	{
		Runtime r =Runtime.getRuntime();
		Process ls_proc;
		String ls_str;
		DataInputStream ls_in;
		FileDialog fd=new FileDialog(this,"Save As",FileDialog.SAVE);
     		fd.setVisible(true);
     		s=fd.getFile();
    		Completepath = fd.getDirectory()+fd.getFile()+".sql";
		try
		{
			if(s.length()>1)
			{
							
			}
		}
			catch(NullPointerException exp)
			{
				JOptionPane.showMessageDialog(null,"The output is saved in file project","",JOptionPane.INFORMATION_MESSAGE);
				Completepath = "project.sql";
			}
		try
		{	
			r.exec("rm "+Completepath);
		}
		catch(Exception e)
		{
		}	
		File f = new File(Completepath);
		Process p = null;
		try
		{
        
	   		
	  		if(input.length() < 1)
			{
				JOptionPane.showMessageDialog(null,"Please Select a Filename to display the output","",JOptionPane.INFORMATION_MESSAGE);	

			}
			
			else
			{	
						
				ls_proc = r.exec("./output "+input);
				ls_in = new DataInputStream(
        			ls_proc.getInputStream());
				try 
				{
					
					line = "";
					while ((ls_str = ls_in.readLine()) != null) 
					{
		    				line = line + ls_str + "\n";
					}
					outLabel.setText(line);
					tabs.setEnabledAt(1,true);
					tabs.setSelectedIndex(1);
					//line = line1 + line;
					/*line = line + "show tables\n;";
					line = line + "desc employee;\n";
					line  = line + "desc department\n;";*/

				}
	    	 		catch (IOException e) 
				{
					System.exit(0);
	    			}
			}
		}
	 	catch (IOException e1) 
		{
	    		System.err.println(e1);
	    		System.exit(1);
	    	}	
		try
		{
			BufferedWriter out = new BufferedWriter(new FileWriter(Completepath,true));
			out.write(line);
			out.close();
		}
		catch(IOException exp)
		{
		}
		
		try{		
		ls_proc = Runtime.getRuntime().exec(new String[] {"sh","-c","mysql < "+Completepath});}
		catch(Exception exception){}
	}
}
if(ae.getSource() == exeinsql)
	{
		try 
		{
			Process ls_proc;
			String line,ls_str;
			DataInputStream ls_in;
			ls_proc = Runtime.getRuntime().exec(new String[] {"sh","-c","mysql < mo.sql"});	
			ls_in = new DataInputStream(
        			ls_proc.getInputStream());
			line = "";
			ls_str = "";	
			while ((ls_str = ls_in.readLine()) != null) 
			{
				line = line + ls_str + "\n";
			}
			mysql.setText(line);
	 		tabs.setEnabledAt(2,true);
			
		}
	    	catch (IOException e) 
		{
			System.out.println(e);
	    	}
				
		tabs.setSelectedIndex(2);
	}




if(ae.getSource()==m6i1)
{
	JOptionPane.showMessageDialog(null,syntax,"",JOptionPane.INFORMATION_MESSAGE);

}
if(ae.getSource()==m6i2)
{
    JOptionPane.showMessageDialog(null,"Key Notes\n\n "+
"KEYWORDS                  EXPLANATION\n\n"+
"vaavs                    Starting point of execution\n"+
"struct                    To define the attribute of a relation,entity or a weak entity\n"+
"weakentitytype        Specifies entity is weak\n"+
"entitytype              Specifies structure is of entity type\n"+
"relationtype           Specifies structure is of entity type\n"+
"pkey                      Specifies that the attribute is a Primary Key\n"+
"mulv                      Specifies that the attribute is a multivalued attribute\n"+
"partialkey               Specifies that the key is of partial type\n"+
"notnull                   Specifies that the key is of not null type\n"+
"database                Specifies the database name\n"+
"unique                   Specifies the attribute is a Unique Attribute\n"+
"relation                  Specifies the relation\n"+
"totpart                   Specifies that the entity is fully dependent\n"+
"identify                  Specifies that the relationship is identifying relationship\n"+
"integer                  Specifies that the attribute is of type integer\n"+
"smallint                 Specifies that the attribute is of type small integer\n"+
"number                 Specifies that the attribute is of type numeric\n"+
"decimal                 Specifies that the attribute is of type decimal\n"+
"double                  Specifies that the attribute is of type double\n"+
"float                     Specifies that the attribute is of type float\n"+
"char                    Specifies that the attribute is of type char\n"+
"varchar                Specifies that the attribute is of type varchar\n"+
"date                     Specifies that the attribute is of type date\n"+
"datetime               Specifies that the attribute is of type datetime\n"+
"timestamp             Specifies that the attribute is of type timestamp\n" ,"",JOptionPane.INFORMATION_MESSAGE);
}  
  
if(ae.getSource()==m6i3)
{
	JOptionPane.showMessageDialog(null,"DATA TYPES\n"+ 
"integer\n"+                                      // step 1
"smallint\n"+
"number     num num \n"+	 
"decimal \n"+
"double     num num \n"+
"float\n"+ 
"char        num\n"+
"varchar    num\n"+
"date\n"+
"dattime\n"+
"timestamp  num \n","",JOptionPane.INFORMATION_MESSAGE);

}

}
  /*
 * @param string
 */
private void Msgbox(String string) {
	// TODO Auto-generated method stub
	
}
public static void main(String a[])
  {
   new editor();
  }
}  //  @jve:decl-index=0:visual-constraint="185,38"
class MyWindowAdapter extends WindowAdapter
{
 editor editor;
 MyWindowAdapter(editor editor)
 {
  this.editor=editor;
 }
 public void windowClosing(WindowEvent we)
 {

  System.exit(0);
 }
}
class myfont extends Dialog implements ActionListener,ItemListener
{
 GraphicsEnvironment ge;
 java.awt.List l1,l2,l3;
 Button b1,b2;
 Font f1[];
 String f[];
 int i,j;
 editor editor;
 TextField tf1,tf2,tf3;
Label ll1,ll2,ll3;
 String fn;
int fs,fsize;
 public myfont(editor myno)
 {
	super(myno,"Font",true);

  setLayout(null);

editor=myno;

  ge=GraphicsEnvironment.getLocalGraphicsEnvironment();
  l1=new java.awt.List();
  l2=new java.awt.List();
  l3=new java.awt.List();
  b1=new Button("OK");
  b2=new Button("CANCEL");
tf1=new TextField(10);
tf2=new TextField(10);
tf3=new TextField(10);
ll1=new Label("Font");
ll2=new Label("Font Style");
ll3=new Label("Size");
	ll1.setBounds(20,60,100,20);
	add(ll1);
	tf1.setBounds(20,80,100,20);
	add(tf1);
        l1.setBounds(20,100,100,150);
        add(l1);
	ll2.setBounds(140,60,100,20);
	add(ll2);
	tf2.setBounds(140,80,100,20);
	add(tf2);
   l2.setBounds(140,100,100,150);
  add(l2);
	ll3.setBounds(260,60,100,20);
	add(ll3);

	tf3.setBounds(260,80,100,20);
	add(tf3);

       l3.setBounds(260,100,100,150);
  add(l3);

	b1.setBounds(380,70,80,20);
  add(b1);
	b2.setBounds(380,95,80,20);
  add(b2);

  f=ge.getAvailableFontFamilyNames();

  for(i=0;i<f.length;i++)
  {
   l1.add(f[i]);
   }

    l2.add("Regular");
l2.add("Bold");
l2.add("Italic");
l2.add("BoldItalic");
   for(i=8;i<=72;i+=2)
	  l3.add(String.valueOf(i));

   b2.addActionListener(this);
   b1.addActionListener(this);
l1.addItemListener(this);
l2.addItemListener(this);
l3.addItemListener(this);
   setSize(480,280);
setResizable(false);
   setVisible(true);

 }


 public void actionPerformed(ActionEvent fe)
 {
  if(fe.getSource()==b2)
  {
   dispose();
   }

  if(fe.getSource()==b1)
	{

	editor.ta.setFont(new Font(fn,fs,fsize));
	dispose();
	}
   }

public void itemStateChanged(ItemEvent ie)
	{

	 if(ie.getSource()==l1)
	  {
   tf1.setText(l1.getSelectedItem());
	fn=tf1.getText();
	   }

	if(ie.getSource()==l2)
	    {
        tf2.setText(l2.getSelectedItem());
	    if(tf2.getText().equals("Bold"))
		  fs=Font.BOLD;

	     else
                if(tf2.getText().equals("Italic"))
		    fs=Font.ITALIC;
	   else
		if(tf2.getText().equals("BoldItalic"))
		      fs=Font.BOLD+Font.ITALIC;
	     else
		    fs=Font.PLAIN;

	if(tf2.getText()=="")
	{
	 tf2.setText("Regular");
 	 fs=Font.PLAIN;
	}
	    }

	if(ie.getSource()==l3)
	  {

	 tf3.setText(l3.getSelectedItem());
	  fsize=Integer.parseInt(tf3.getText());
              if(tf3.getText()=="")
		{
  			fsize=8;
		}
               }
	}
}


class search extends Frame implements ActionListener
{
 TextField tf;
 Button b3,b4;
 Checkbox up,dn,mc;
 CheckboxGroup cbg;
 Label l1;
 editor editor;
 String s,s1;
 int l,k,si,ei,i=0;
StringBuffer sb;
public  search(editor editor)
 { setTitle("Find");

this.editor=editor;
  l1=new Label("Find");
  tf=new TextField(30);
  b3=new Button("FindNext..");
  b4=new Button("Cancel");
  cbg=new CheckboxGroup();
  up=new Checkbox("up",cbg,false);
  dn=new Checkbox("down",cbg,true);
  mc=new Checkbox("Match Case");
  setLayout(null);
   l1.setBounds(20,60,100,20);
   add(l1);
                    tf.setBounds(20,80,100,20);
   add(tf);
   b3.setBounds(140,60,100,20);
   add(b3);
   b4.setBounds(140,90,100,20);
   add(b4);
   mc.setBounds(10,120,90,10);
   add(mc);
  //setBackground(Color.BLUE);
setSize(300,200);
setVisible(true);
b3.addActionListener(this);
b4.addActionListener(this);

  }
public void actionPerformed(ActionEvent e1)
  {

   if(e1.getSource()==b4)
   {
    dispose();
   }
   if(e1.getSource()==b3)
   {
   s=editor.ta.getText();
    l=s.length();
 sb=new StringBuffer(s);
    s1=tf.getText();
    k=s1.length();
    //si=sb.indexOf(s1);
    ei=si+(k);
    editor.ta.select(si,ei);
     }
   }
 }
/*class help extends Frame implements ActionListener
{
 TextArea l;
 Button b;
 editor editor;
 help(editor editor)
 { setLayout(null);
  this.editor=editor;
  l=new TextArea(editor.s,100,100);
  b=new Button("CLOSE");
  add(l);
  b.setBounds(30,70,70,20);
  add(b);
  b.addActionListener(this);
 }
 public void actionPerformed(ActionEvent ae2)
 {
  if(ae2.getSource()==b)
  {
   dispose();
  }
 }
}*/
