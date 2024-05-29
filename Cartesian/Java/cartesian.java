/*
 *  Cartesian Robot driver - Java version
 *
 *  Adrian Bowyer
 *  24 September 2005
 *
 */

import java.io.*;


// Integer and real 3D vectors

class i_3point
{
    public int x, y, z;
    public boolean flag;

    public i_3point()
    {
	x = 0;
	y = 0;
	z = 0;
	flag = false;
    }

    public i_3point(int xx, int yy, int zz)
    {
	x = xx;
	y = yy;
	z = zz;
	flag = true;
    }  

    public i_3point(i_3point i)
    {
	x = i.x;
	y = i.y;
	z = i.z;
	flag = i.flag;
    }  

    public String toString()
    {
	return Integer.toString(x) + " " + Integer.toString(y) + " " + Integer.toString(z);
    }
}

class rr_3point
{
    public double x, y, z;
    public boolean flag;

    public rr_3point()
    {
	x = 0;
	y = 0;
	z = 0;
	flag = false;
    }

    public rr_3point(rr_3point r)
    {
	x = r.x;
	y = r.y;
	z = r.z;
	flag = r.flag;
    }

    public rr_3point(double xx, double yy, double zz)
    {
	x = xx;
	y = yy;
	z = zz;
	flag = true;
    }  

    public String toString()
    {
	return Double.toString(x) + " " + Double.toString(y) + " " + Double.toString(z);
    }
}

class cartesian
{
    static final String port = "/dev/ttyS0";  // The serial port
    static final double scale = 40.0;         // Steps/mm
    static final double speedsteps = 1706.67; // Count = speedsteps/v
    static final int END_FIND = 20000;        // Steps to go to find zero/max
    static final int OFFSET = 100;            // Offset from hard zero
    static final int ST_LEN = 200;            // Maximum command string length
    static final int DEF_SC = 768;            // Default value of the speedcount
    static final int DEF_AC = 368;            // Default value of the accelleration count
    static final int DEF_IC = 1;              // Default value of the accelleration increment
    static final int DEF_SIC = 1;             // Default value of the steps per increment

    private c_file s_port;                    // The serial port the robot's on
    private i_3point max;                     // Maximum axis positions
    private boolean waiting;                  // Robot active, so wait
    private boolean setup;                    // Flag for initializing - allows working outside envelope
    private int mc;                           // Move count
    private int re_z;                         // Re-zero every re_z moves
    private double half_step;                 // 1 for normal; 2 for half-stepping
    private String state_file;                // File name for storing the state
    private boolean init;                     // Has the structure been properly initialized?
    private File dbf;                         // Debug output...
    private PrintWriter dbo;                  // ...stream



    // Constructor with reset option

    public cartesian(boolean rezero)
    {
	s_port = new c_file(port);
	waiting = false;
	setup = true;
	init = false;
	dbf = null;
	dbo = null;
	half_step = 1;
	max = new i_3point();

	state_file = "";

	String henv = System.getProperty("user.home"); 
 
	if(henv.length() <= 0)  
	    System.err.println("Can't get $HOME environment variable.");
	else
	    {
		state_file = henv + "/.cartesian";
		File f = new File(state_file);
		if(!(f.exists() && f.isDirectory()))
		    {
			File st = new File(henv, "/.cartesian");
			st.mkdir();
			System.out.println("Creating directory: " + state_file);
		    }
		state_file = state_file + "/state";
	    }

	String s;

	wr(".");         // Reset robot
	delay(100);
	wr("e");         // Robot echo off
	delay(100);
	s = rd();        // Absorb whatever the robot has sent

	mc = 0;

	if(!load())
	    {

		// Didn't load from file, so re-initialize other data

		mc = -1;               // Force re-zero
	    }

	if(rezero || (mc == -1))
	    {
		mc = 0;
		re_zero();
	    }

	mc = 0;
	re_z = -1;
	setup = false;
	init = true;
    } 


    // Pad a string with leading 0s out to n bytes

    private static String zPad(String s, int n)
    {
	while(s.length() < n) s = "0" + s;
	return s;
    }

    // Turn n into hex in String h

    private static String n2hex(byte n)
    {
	return zPad(Integer.toString(n, 16).toLowerCase(), 2);
    }

    // Turn hex in h into a number and return it

    private static byte hex2n(String h)
    {
	if (h.length() > 2)
	    {
		System.err.println("hex2n: more than three characters.");
		return 0;
	    }
	return (byte) Integer.parseInt(h, 16);
    }

    // Convert 24-bit numbers to/from hex

    private static int hex2long(String h)
    {
	return Integer.parseInt(h, 16);
    }

    private static String long2hex(int n)
    {
	n = n & 0xffffff;
	return zPad(Integer.toString(n, 16).toLowerCase(), 6);
    }

    // Send the string s to the robot

    private void wr(String str)
    {
	// Check init (setup needs access before init is set)

	if(!init && !setup)
	    {
		System.err.println("Attempt to use robot before it's been initialized.");
		if(dbf != null)
		    dbo.println("  Attempt to use robot before it's been initialized.");
	    }

	if(waiting)
	    {
		if(dbf != null)
		    dbo.println("  wr(...) called while waiting.");
		String s;
		s = rd(2);
		waiting = false;
	    }

	int n = s_port.write(str, str.length());
	if(dbf != null)
	    {
		dbo.println("  \"" + str + "\" sent to the robot.  ");
		dbo.println("write(...) call returned: " + n);
	    }
	if (n != str.length())
	    {
		System.err.println("write(...) failed on: \"" + str + "\"");
		if(dbf != null)
		    dbo.println("  write(...) failed on: \"" + str + "\"");
	    }

    } 

    // Read whatever the robot says (including nothing) into str

    private String rd()
    {
	String result = "";
	s_port.fcntl(0);
	result = s_port.read();
	int nc = s_port.n_read();

	if(dbf != null)
	    {
		dbo.println("  \"" + result + "\" returned from the robot.  ");
		dbo.println("read(...) call returned: " + nc);
	    }
	s_port.fcntl(1);
	return result;
    } 

    // Read n bytes into str, waiting if need be
 
    private String rd(int n)
    {
	String result = s_port.read();
	int nc = s_port.n_read();

	if(nc != n)
	    {
		System.err.println("rd(" + n + "): read failed. Returned string: \"" + result + "\"");
		if(dbf != null)
		    {
			dbo.println("  rd(" + n + "): read failed. Returned string: \"" + result + "\"");
			dbo.flush();
		    }
	    }

	if(dbf != null)
	    {
		dbo.println("  \"" + result + "\" returned from the robot.  ");
		dbo.println("read(...) call returned: " + nc);
	    }
	return result;
    } 

    // Convert integer coordinates to mm

    public rr_3point step2pos(i_3point i) 
    {
	rr_3point r = new rr_3point();
	r.x = (double)i.x/(scale*half_step);
	r.y = (double)i.y/(scale*half_step);
	r.z = (double)i.z/(scale*half_step);
	r.flag = true;
	return r;
    } 

    // Convert mm to integer coordinates

    public i_3point pos2step(rr_3point r) 
    {
	i_3point i = new i_3point();
	i.x = (int)(r.x*scale*half_step + 0.5);
	i.y = (int)(r.y*scale*half_step + 0.5);
	i.z = (int)(r.z*scale*half_step + 0.5);
	i.flag = true;
	return i;
    } 

    // Send destination (integer coordinates)

    private boolean idest(i_3point i)
    {
	if(!setup)  // setup needs to go beyond the envelope
	    {
		if( (i.x > max.x) || (i.y > max.y) || (i.z > max.z) ||
		    (i.x < 0) || (i.y < 0) || (i.z < 0) ) 
		    {
			if(dbf != null)
			    dbo.println("  Attempt to move outside the envelope to (" + i.toString() + ")");
			return(false);
		    }
	    }

	if(dbf != null)
	    dbo.println(" Sending coordinates: (" + i.toString() + ") to the robot.");

	String s;

	s = long2hex(i.x);
	wr("A");
	wr(s);

	s = long2hex(i.y);
	wr("B");
	wr(s);

	s = long2hex(i.z);
	wr("C");
	wr(s);
	return(true);
    } 

    // Send destination (real coordinates)

    public boolean dest(rr_3point r)
    {  
	i_3point i = pos2step(r);
	return(idest(i));
    } 

    // Get position (integer coordinates)

    private i_3point ipos()
    {
	String s;
	i_3point i = new i_3point();

	wr("a");
	s = rd(6);
	i.x = hex2long(s);
	wr("b");
	s = rd(6);
	i.y = hex2long(s);
	wr("c");
	s = rd(6);
	i.z = hex2long(s);
	i.flag = true;

	if(dbf != null)
	    dbo.println(" Coordinates: (" + i.toString() + ") received from the robot.");
	
	return i;
    } 

    // Destination loaded - go there quick

    private void q()
    {
	if(half_step > 1.5)
	    wr("h");     // Half stepping
	else
	    wr("q");     // Low torque

	wr("F");     // Fast move
	waiting = true;
	mc++;
	if((re_z > 0) && ((mc%re_z) == 0))
	    zero_test();
    } 

    // Destination loaded - go there at constant speed

    private void g()
    {
	if(half_step > 1.5)
	    wr("h");     // Half stepping
	else
	    wr("Q");     // High torque

	wr("f");     // Constant speed 
	waiting = true;
	mc++;
	if((re_z > 0) && ((mc%re_z) == 0))
	    zero_test();
    } 

    // Save and load the robot's state

    public boolean save()
    {
	File opf;
	PrintWriter op;

	if(state_file.length() <= 0)	    
	    {
		System.err.println("State file name has zero length");
		return false;
	    }

	try
	    {
		opf =  new File(state_file);
		op =  new PrintWriter(new FileWriter(opf));
	    }
	catch(IOException err)
	    {
		System.err.println("Can't open state file:" + state_file);
		return false;
	    }

	op.println(half_step);
	i_3point i = ipos();
	op.println(i.toString());
	op.println(max.toString());
	op.println(mc);
	int speedcount = get_speedcount();
	int acccount = get_acccount();
	int inccount = get_inccount();
	int stcount = get_stcount();
	op.println(speedcount);
	op.println(acccount);
	op.println(inccount);
	op.println(stcount);
	op.println(init);
	op.close();
	return true;
    } 

    private boolean load()
    {
	BufferedReader inp;

	if(state_file.length() <= 0)	    
	    {
		System.err.println("State file name has zero length");
		return false;
	    }

	try
	    {
		inp =  new BufferedReader(new FileReader(new File(state_file)));
	    }
	catch(IOException err)
	    {
		System.err.println("Can't open state file: " + state_file);
		return false;
	    }

	TextReader ip = new TextReader(inp);

	half_step = ip.getDouble();
	i_3point i = new i_3point();
	i.x = ip.getInt();
	i.y = ip.getInt();
	i.z = ip.getInt();
	idest(i);
	wr("p");
	max = new i_3point();
	max.x = ip.getInt();
	max.y = ip.getInt();
	max.z = ip.getInt();

	mc = ip.getInt();
	int speedcount, acccount, inccount, stcount;
	speedcount = ip.getInt();
	acccount = ip.getInt();
	inccount = ip.getInt();
	stcount = ip.getInt();
	set_speed(speedcount, acccount, inccount, stcount);
	init = ip.getBoolean();
	try
	    {
		inp.close();
	    }
	catch(IOException err)
	    {
		System.err.println("Can't close state file: " + state_file);
		return false;
	    }
	return true;
    } 


    // Set/get the speed and accelleration

    public void set_speed(int speedcount, int acccount, int inccount, int stcount)
    {
	String s;
	s = long2hex(speedcount);
	wr("T");
	wr(s);
	s = long2hex(acccount);
	wr("S");
	wr(s);
	s = long2hex(inccount);
	wr("J");
	wr(s);
	s = long2hex(stcount);
	wr("I");
	wr(s);
    } 


    public int get_speedcount()
    {
	String s;
	wr("t");
	s = rd(6);
	return hex2long(s);
    }

    public int get_acccount()
    {
	String s;
	wr("s");
	s = rd(6);
	return hex2long(s);
    }

    public int get_inccount()
    {
	String s;
	wr("j");
	s = rd(6);
	return hex2long(s);
    }

    public int get_stcount()
    {
	String s;
	wr("i");
	s = rd(6);
	return hex2long(s);
    } 


    // Sleep for a time.

    public static void delay(int milliseconds)
    {
	try  // Wait...
	    {
		Thread.sleep(milliseconds);
	    }
	catch (InterruptedException e)
	    {
		return;
	    }
    }


    // Get the robot's current position

    public rr_3point pos()
    {
	i_3point i = ipos();
	return step2pos(i);
    } 

    // Get the robot's working envelope

    public rr_3point envelope()
    {
	return step2pos(max);
    } 
  
    // Move linearly to a position

    public boolean go(rr_3point r)
    {
	if(!dest(r)) return(false);
	g();
	return(true);
    } 

    // Move to a position directly

    public boolean quick(rr_3point r)
    {
	if(!dest(r)) return(false);
	q();
	return(true);
    } 

    // Move to the safe position (x =  0, y = 0, z = zmax)

    public void safe()
    {
	i_3point i = ipos();
	i.z = max.z;
	idest(i);  // Straight up is safest
	q();
	i.x = 0;
	i.y = 0;
	idest(i);
	q();
    } 

    // Re-establish the zero position

    public void re_zero()
    {
	setup = true;
	wr("r");         // Set current position to 0
	delay(100);
	i_3point i = new i_3point(-END_FIND, 0, 0);
	idest(i);
	q();

	wr("r");         // Set current position to 0
	delay(100);
	i = new i_3point(0, -END_FIND, 0);
	idest(i);
	q();

	wr("r");         // Set current position to 0
	delay(100);
	i = new i_3point(0, 0, -END_FIND);
	idest(i);
	q();

	wr("r");
	delay(100);
	i = new i_3point(OFFSET, OFFSET, OFFSET);
	idest(i);
	g();
	wr("r");

	int d1=0, d2=0;
	i = new i_3point(END_FIND, 0, 0);
	idest(i);
	q();

	i = ipos();
	max.x = i.x;
	i = new i_3point(max.x, END_FIND, 0);
	idest(i);
	q();

	i = ipos();
	max.y = i.y;
	i = new i_3point(max.x, max.y, END_FIND);
	idest(i);
	q();

	i = ipos();

	max.x = max.x - OFFSET;
	max.y = max.y - OFFSET;
	max.z = i.z - OFFSET;

	i = new i_3point(0, 0, max.z);
	idest(i);
	q();
	setup = false;
    } 

    // Test and re-establish the zero position

    public void zero_test()
    {
	i_3point i = ipos();

	safe();

	setup = true;  

	i_3point j = new i_3point(-END_FIND, 0, max.z);
	idest(j);
	q();

	j = new i_3point(0, -END_FIND, max.z);
	idest(j);
	q();

	j = new i_3point(0, 0, END_FIND);
	idest(j);
	q();

	i_3point e = ipos();

	if(dbf != null)
	    dbo.println("Zero test. x error: " + (OFFSET + e.x) + ", y error: "  + (OFFSET + e.y) + 
			", z error: " + (max.z + OFFSET - e.z));
  
	wr("r");
	delay(100);

	j = new i_3point(OFFSET, OFFSET, -OFFSET);
	idest(j);
	g();
	j = new i_3point(0, 0, max.z);
	idest(j);
	wr("p");

	setup = false;

	j = new i_3point(i);
	j.z = max.z;
	idest(j);
	q();
	idest(i);
	q();
    } 

    // Test and re-establish the zero position every n moves
    // Set n -ve to supress

    public void repeat_zero(int n)
    {
	if(n <= 0)
	    re_z = -1;
	else
	    re_z = n;
    } 

    // Set the speed, acceleration, etc

    public boolean speed(double v, double rate, double time)
    {
	int speedcount, acccount, inccount, stcount;

	speedcount = (int)(0.5 + speedsteps/v);
	if(speedcount < 1) 
	    {
		speedcount = 1;
		return(false);
	    }

	// Acceleration distance

	double d = v*time + 0.5*rate*time*time;
	acccount = (int)(0.5 + d*scale*half_step);

	// Acceleration gradient

	double final_v = v + rate*time;
	long delta_count = (int)(0.5 + speedsteps/final_v) - speedcount;
	if(delta_count < acccount)
	    {
		inccount = 1;
		stcount = (int)(0.5 + (double)acccount/(double)delta_count);
	    } else
	    {
		inccount = (int)(0.5 + (double)delta_count/(double)acccount);
		stcount = 1;
	    }

	set_speed(speedcount, acccount, inccount, stcount);

	return(true);
    } 

    // Half stepping on (hs == 1) or off (hs = 0)

    public void half(boolean hs)
    {
	if(hs)
	    {
		half_step = 2;

	    } else
	    {
		half_step = 1;

	    }
    } 

    // Write a byte to the user port

    public void user_port(byte b)
    {
	String s;

	wr("L00");
	wr("K");
	s = n2hex(b);
	wr(s);
    } 

    // Read a byte from the user port

    public byte user_port()
    {
	String s;

	wr("L3f");
	wr("k");
	s = rd(2);
	return hex2n(s);
    } 

    // Read a voltage from an A to D channel (answer is between 0.0 and 5.0)

    public double volt(int c)
    {
	return 0;
    } 

    // Set the user's endstop for X and Y (1 for on, 0 for off)

    public void stop_xy(int on)
    {
    } 

    // Set the user's endstop for Z (1 for on, 0 for off)

    public void stop_z(int on)
    {
    } 

    // Debug to file db_file (empty string switches debugging off)

    public void debug(String db_file)
    {
	if(db_file.length() > 0)
	    {
		try
		    {
			dbf = new File(db_file);
			dbo = new PrintWriter(new FileWriter(dbf));
			dbo.println("Cartesian robot debug file:");
		    }
		catch(IOException err)
		    {
			System.err.println("Can't open debug file: " + db_file);
		    }
	    } else
	    {
		if(dbf != null)
		    {
			dbo.println("\nDebugging shut down.");
			dbo.close();
			dbf = null;
		    }
	    } 
    } 

    // Read in a file of coordinates and execute it

    public boolean do_file(String f_name)
    {
	BufferedReader inp;
	try
	    {
		inp =  new BufferedReader(new FileReader(new File(f_name)));
	    }
	catch(IOException err)
	    {
		System.err.println("Can't open input file: " + f_name);
		return false;
	    }

	TextReader ip = new TextReader(inp);

	rr_3point r = new rr_3point();
	int q;

	long count = 1;

	System.out.println("");

	while(!ip.eof())
	    {
		q = ip.getInt();
		r.x = ip.getDouble();
		r.y = ip.getDouble();
		r.z = ip.getDouble();
		switch(q)
		    {
		    case 0:
			System.out.println("Move " + count + " quickly to (" + r.toString() + ")");
			if(!quick(r))
			    {
				System.out.println("  Illegal position: " + r.toString() + " at move: " + count);
			    }
			break;
		    
		    case 1:
			System.out.println("Move " + count + " slowly to " + r.toString() + ")");
			if(!go(r))
			    {
				System.out.println("  Illegal position: " + r.toString() + " at move: " + count);
			    }
			break;

		    case 2:
			System.out.println("Mark " + count + " slowly to " + r.toString() + ")");
			user_port((byte)0);
			if(!go(r))
			    {
				System.out.println("  Illegal position: " + r.toString() + " at move: " + count);
			    }
			user_port((byte)4);
			break;
		    }
		count++;
	    }
	System.out.println("");

	try
	    {
		inp.close();
	    }
	catch(IOException err)
	    {
		System.err.println("Can't close input file: " + f_name);
		return false;
	    }
	return true;
    }
}

