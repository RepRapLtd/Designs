package rangeGenerator;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RangeGenerator 
{
	static String inputFileName = "range1.txt";
	static double[] centre = new double[2];
	static double angleIncrement = 10.0;
	static double outOfRange = 3000.0;
	static double accuracy = 1.0e-10;
	
	// double[x/y][0/g]
	
	static ArrayList<double[][]> segments = new ArrayList<double[][]>();
	static ArrayList<Double> hits = new ArrayList<Double>();
	
	public static void main(String[] args)
	{
		readSegments(false);
		//printSegments();
		scan();
		printHits();
		printRays();
	}
	
	public static void printHits()
	{
		double angle = 0.0;
		int i = 0;
		while(angle < 360.0)
		{
			double[][] ray = getRay(angle);

			double pMin = hits.get(i);
			System.out.println( Double.toString(ray[0][0]+ray[0][1]*pMin) + "," +
					Double.toString(ray[1][0]+ray[1][1]*pMin) );			
			i++;
			angle += angleIncrement;
		}				
	}
	
	public static void printRays()
	{
		System.out.println(
				Double.toString(centre[0]) + "," + 
				Double.toString(centre[1]) + "," +
				Double.toString(angleIncrement)
				);
		for(int i = 0; i < hits.size() - 1; i++)
			System.out.println( Double.toString(hits.get(i)) );						
	}
	
	public static double[][] getRay(double angle)
	{
		double[][] ray = new double[2][2];
		ray[0][0] = centre[0];
		ray[1][0] = centre[1];
		double a = angle*Math.PI/180.0;
		ray[0][1] = Math.cos(a);
		ray[1][1] = Math.sin(a);
		return ray;
	}
	
	public static void scan()
	{
		double angle = 0.0;
		while(angle < 360.0)
		{
			double[][] ray = getRay(angle);

			double pMin = Double.MAX_VALUE;
			for(int i = 0; i < segments.size(); i++)
			{
				double[] parameters = rayStrike(ray, segments.get(i));
				if(parameters[0] >= 0.0 && parameters[0] < pMin && parameters[1] >= 0.0 && parameters[1] <= 1.0)
					pMin = parameters[0];
			}
			if(pMin > outOfRange || pMin < 0.0)
			{
				//System.out.println("miss");
				hits.add(outOfRange);
			}
			else
			{
				//System.out.println("hit: (" + Double.toString(ray[0][0]+ray[0][1]*pMin) + ", " +
						//Double.toString(ray[1][0]+ray[1][1]*pMin) + ").");
				hits.add(pMin);
			}
			angle += angleIncrement;
		}		
	}
	
	 // p[0][0] - x origin; p[1][0] - y origin
	 // p[0][1] - x gradient; p[1][1] - y gradient

	public static double[] rayStrike(double[][] ray, double[][] segment)
	{
		double[] parameters = new double[2];
		double gradCross1 = ray[0][1] * segment[1][1];
		double gradCross2 = ray[1][1] * segment[0][1];
		double det = gradCross2 - gradCross1;
		
		if(Math.abs(det) < accuracy)
		{
			parameters[0] = outOfRange + 10.0;
			parameters[1] = 0.0;
			return parameters;			
		}
		
		double xDif = segment[0][0] - ray[0][0];
		double yDif = segment[1][0] - ray[1][0];
		det = 1.0/det;
		parameters[0] = (segment[0][1]*yDif - segment[1][1]*xDif)*det;
		parameters[1] = (ray[0][1]*yDif - ray[1][1]*xDif)*det;
		return parameters;
	}
	
	public static void readSegments(boolean pairs)
	{
        String line = null;
        Pattern p = Pattern.compile("(\\d+(?:\\.\\d+))");
        Matcher m = null;
        boolean firstLine = true;
        
        try 
        {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFileName));

            while((line = bufferedReader.readLine()) != null) 
            {
            	//System.out.println(line);
        		m = p.matcher(line);
            	if(firstLine)
            	{
                    m.find();
                    centre[0] = Double.parseDouble(m.group(1));
                    m.find();
                    centre[1] = Double.parseDouble(m.group(1));
                    m.find();
                    angleIncrement = Double.parseDouble(m.group(1));
                    firstLine = false;
            	} else
            	{
            		double[][] d = new double[2][2];
            		if(pairs)
            		{
	            		m.find();
	            		d[0][0] = Double.parseDouble(m.group(1)); // x0
	            		m.find();
	            		d[1][0] = Double.parseDouble(m.group(1)); // y0
	            		m.find();
	            		d[0][1] = Double.parseDouble(m.group(1)); // x1
	            		m.find();
	            		d[1][1] = Double.parseDouble(m.group(1)); // y1
	            		
	            		d[0][1] = d[0][1] - d[0][0];
	            		d[1][1] = d[1][1] - d[1][0];
	            		
            		} else
            		{
	            		m.find();
	            		d[0][1] = Double.parseDouble(m.group(1)); // x1
	            		m.find();
	            		d[1][1] = Double.parseDouble(m.group(1)); // y1  			
            		}
            		            		
            		segments.add(d);
            	}
            }   

            bufferedReader.close();
            
            if(!pairs)
            {
            	int j = segments.size() - 1;
            	for(int i = 0; i < segments.size(); i++)
            	{
            		double[][] d0 = segments.get(j);
            		double[][] d1 = segments.get(i);
            		d1[0][0] = d0[0][1];
            		d1[1][0] = d0[1][1];
            		segments.set(i, d1);
            		j = i;            		
            	}
            	
            	for(int i = 0; i < segments.size(); i++)
            	{
            		double[][] d = segments.get(i);
            		d[0][1] = d[0][1] - d[0][0];
            		d[1][1] = d[1][1] - d[1][0];
            		segments.set(i, d);
            	}
            }
        }
        
        catch(FileNotFoundException ex) 
        {
            System.out.println("Unable to open file '" + inputFileName + "'");                
        }
        
        catch(IOException ex) 
        {
            System.out.println("Error reading file '" + inputFileName + "'");                  
        }
	}
	
	public static void printSegments()
	{
		System.out.println("Centre (x, y): (" + Double.toString(centre[0]) + ", " + 
				Double.toString(centre[1]) + ").");
		System.out.println("Angle increment: " + Double.toString(angleIncrement));
		for(int i = 0; i < segments.size(); i++)
		{
			double[][] d = segments.get(i);
			System.out.println("  Parametric: (" + Double.toString(d[0][0]) + ", " + 
					Double.toString(d[1][0]) + "), (" + Double.toString(d[0][1]) + ", " + 
					Double.toString(d[1][1]) + ")." );
		}		
	}
}
