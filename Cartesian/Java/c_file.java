/*
 *  Low-level C file interface via JNI
 *
 *  Adrian Bowyer
 *  2 October 2005
 *
 */

// Teeny class to hold the JNI calls to some C functions that access
// low-level file setup, reading and writing

class c_c_file
{
    public native int c_open(String file_name);              // Open file, returning a descriptor
    public native void c_fcntl(int fd, int wait);            // Wait (or not) for input
    public native int c_write(int fd, String str, int len);  // Write len bytes of str (number actually sent is returned)
    public native String c_read(int fd);                     // Read into string
    public native int c_n_read();                            // Number of bytes read by c_read()

    static 
    {
        System.loadLibrary("c_c_file");	// load the .so file with the native fns.
    }
}

// Wrapper class for c_c_file; this retains the static instance 
// of it and the file descriptor, so the rest of the software doesn't
// need to care about them.

class c_file
{
    private static int fd;                    // C file descriptor of the file
    private static c_c_file ccf;              // Instance of the C JNI calls.

    // The constructor opens the file

    public c_file(String file_name)
    {
	ccf = new c_c_file();
	fd = ccf.c_open(file_name);
	if(fd == -1)
	    System.err.println("Unable to open file:" + file_name);	    
    }

    // Wait 1 (or not 0) for input

    public void fcntl(int wait)
    {
	ccf.c_fcntl(fd, wait);
    }

    // Write len bytes of str (number actually sent is returned)

    public int write(String str, int len)
    {
	return ccf.c_write(fd, str, len);
    }

    // Read into string

    public String read()
    {
	return ccf.c_read(fd);
    }

    // Number of bytes read by last call to c_read()
    // (Nasty.  But simple...)

    public int n_read()
    {
	return ccf.c_n_read();
    }
}
