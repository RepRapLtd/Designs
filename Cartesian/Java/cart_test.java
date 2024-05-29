/*
 *  Cartesian Robot driver - Test program
 *
 *  Adrian Bowyer
 *  24 September 2005
 *
 */

class cart_test
{
    // Main program is just a big command loop

    public static void main(String[] args)
    {
	cartesian c = new cartesian(false);

	double x1, y1, z1, rad, theta;
	int speedcount, acccount, inccount, stcount;
	byte b;
	int stp, lp, rz;
	String f_name;
	String k;

	rr_3point r = new rr_3point(c.envelope());
	rr_3point rr, rrr;

	System.out.println("envelope: " + r.toString());

	// Loop, reading commands and acting on them

	TextReader in = new TextReader(System.in);

	c.user_port((byte)4);

	do
	    {
		System.out.print("\nCommand: ");
		k = in.getWord();
		if(k.equals("p"))
		    {
			r = new rr_3point(c.pos());
			System.out.print("Position: (" + r.toString() + ") mm");
		    } else if( k.equals("a")) 
		    {
			System.out.print("X, Y, Z to accelerate and decelerate to (mm): ");
			r.x = in.getDouble();
			r.y = in.getDouble();
			r.z = in.getDouble();
			if(!c.quick(r))
			    {
				System.out.println("Illegal position.");
				r = new rr_3point(c.envelope());
				System.out.println("Robot's envelope is: (" + r.toString() + ")");
			    }
		    } else if( k.equals("b")) 
		    {
			b = c.user_port();
			System.out.println("User port byte: " + Byte.toString(b));
		    } else if( k.equals("B")) 
		    {
			System.out.print("Byte to send: ");
			b = in.getByte();
			c.user_port(b);
		    } else if( k.equals("g")) 
		    {
			System.out.print("X, Y, Z to move at constant speed to (mm): ");
			r.x = in.getDouble();
			r.y = in.getDouble();
			r.z = in.getDouble();
			if(!c.go(r))
			    {
				System.out.println("Illegal position.");
				r = new rr_3point(c.envelope());
				System.out.println("Robot's envelope is: (" + r.toString() + ")");
			    }
		    } else if(k.equals("G")) 
		    {
			System.out.print("X, Y, Z to move at constant speed to (mm): ");
			r.x = in.getDouble();
			r.y = in.getDouble();
			r.z = in.getDouble();
			c.user_port((byte)0);
			if(!c.go(r))
			    {
				System.out.println("Illegal position.");
				r = c.envelope();
				System.out.println("Robot's envelope is: (" + r.toString() + ")");
			    }
			c.user_port((byte)4);
		    } else if(k.equals("s")) 
		    {
			c.safe();
		    } else if(k.equals("0")) 
		    {
			c.re_zero();
		    } else if(k.equals("v")) 
		    {
			System.out.print("Velocity (mm/s): ");
			r.x = in.getDouble();
			System.out.print("Rate (mm/s^2): ");
			r.y = in.getDouble();
			System.out.print("Time (s): ");
			r.z = in.getDouble();
			c.speed(r.x, r.y, r.z);
		    } else if( k.equals("c")) 
		    {
			System.out.print("Centre (x, y): ");
			r.x = in.getDouble();
			r.y = in.getDouble();
			System.out.print("Height (z): ");
			r.z = in.getDouble();
			System.out.print("Radius: ");
			rad = in.getDouble();
			System.out.print("Steps: ");
			stp = in.getInt();
			rr = new rr_3point(c.pos());
			rrr = new rr_3point(rr);
			rr.x = r.x + rad;
			rr.y = r.y;
			c.quick(rr);
			rr.z = r.z;

			c.go(rr);
			for(int i = 0; i <= stp; i++)
			    {
				theta = 2*Math.PI*(double)i/(double)stp;
				rr.x = r.x + rad*Math.cos(theta);
				rr.y = r.y + rad*Math.sin(theta);
				c.go(rr);
			    }
			rr.z = rrr.z;
			c.go(rr);
			c.quick(rrr);
		    } else if( k.equals("D")) 
		    {
			System.out.print("File name for debugging information: ");
			f_name = in.getWord();
			c.debug(f_name);
			System.out.println("Debugging is ON.");
		    } else if( k.equals("d")) 
		    {
			c.debug("");
			System.out.println( "Debugging is OFF.");
		    } else if( k.equals("f") || k.equals("F")) 
		    {
			System.out.print("Name of the coordinate file: ");
			f_name = in.getWord();
			if(k.equals("F"))
			    {
				System.out.print("Number of times to loop file: ");
				lp = in.getInt();
				for(int i = 0; i < lp; i++)
				    c.do_file(f_name);
			    } else
			    c.do_file(f_name);
		    } else if( k.equals("t")) 
		    {
			c.zero_test();
		    } else if( k.equals("H")) 
		    {
			c.half(true);
			System.out.println("Half stepping is ON.");
		    } else if( k.equals("h")) 
		    {
			c.half(false);
			System.out.println("Half stepping is OFF.");
		    } else if( k.equals("z")) 
		    {
			System.out.print("Re-zero after how many moves (-ve to supress)? ");
			rz = in.getInt();
			c.repeat_zero(rz);
		    } else if( k.equals("n")) 
		    {
			System.out.println("Steps per delay: " + c.get_speedcount());
			System.out.println("Steps to accelerate/decelerate for: " + c.get_acccount());
			System.out.println("Change speed every " + c.get_inccount() + " steps");
			System.out.println("Change speed by " + c.get_stcount() + " steps");
		    } else if( k.equals("N"))
		    {
			System.out.print("Steps per delay: "); 
			speedcount = in.getInt();
			System.out.print("Steps to accelerate/decelerate for: ");
			acccount = in.getInt();
			System.out.print("When accelerating, change speed after how many steps: ");
			inccount = in.getInt();
			System.out.print("When accelerating, change speed by how many steps: ");
			stcount = in.getInt();
			c.set_speed(speedcount, acccount, inccount, stcount);
		    } else if( k.equals("q")) 
		    {
		    } else
		    {  
			System.out.println("Commands are:");
			System.out.println("D - debug on");
			System.out.println("d - debug off");      
			System.out.println("p - print position");
			System.out.println("a - accelerate and decelerate to a position");
			System.out.println("g - move at constant speed to a position");
			System.out.println("G - move at constant speed to a position with user on/off");
			System.out.println("H - half-stepping ON");
			System.out.println("h - half-stepping OFF");
			System.out.println("n - print the accelleration parameters");
			System.out.println("N - set the acceleration parameters");
			System.out.println("s - move to the safe position");
			System.out.println("b - reat a byte from the user port");
			System.out.println("B - write a byte to the user port");
			System.out.println("0 - re-establish the origin");
			System.out.println("v - set speed and acceleration");
			System.out.println("c - describe a circle");
			System.out.println("f - read moves from a file and execute them");
			System.out.println("F - read moves from a file and execute them in a loop");
			System.out.println("t - test and re-establish the zero position");
			System.out.println("z - test and re-establish the zero position every n moves");
			System.out.println("q - quit");
		    }
	    } while(!k.equals("q"));
	c.save();
    }
}

