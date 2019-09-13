/*

Parametric Ducting Flap Vent

Adrian Bowyer

RepRap Professional Ltd
http://reprappro.com

10 August 2013

Licence: GPL

All dimensions are in mm.

*/

duct_d = 300;      // Duct hole diameter
n_flaps = 5;       // Number of flaps - should be odd
big_gap = 5;       // Duct hole to frame inner edge distance
thick = 5;         // Section thickneses
small_gap = 2;     // Gap between flap and frame edge
edge = 20;         // width of edge
flap_thick = 1.0;  // Flap thickness
M3_rad = 1.7;      // M3 screw

// Uncomment these two to see the entire assembly with
// the flaps at the angle specified

color("red")
 frame();
color("green")
 all_flaps(false, ang = 45);

// Uncomment this to see the relative size of the duct

//duct();

// Uncomment this to see a single flap at an agle of 6 degrees

//flap(rods = false, ang = 6);

// To split to manageable sizes for printing generate four of these
// quarters with angles of 0, 90, 180, and 270 plus...

//quarter(270);

// ... n_flaps half_flaps with an angle of 0 and n_flaps half_flaps with 180.

//half_flap(0);

module half_flap(ang=0)
{
	intersection()
	{
		flap(rods = false, ang = 0);
		rotate([0,0,ang])
			translate([0,-duct_d/2,-duct_d/2])
				cube([duct_d*2, duct_d*2, duct_d]);
	}	
}

module quarter(ang=0)
{
	intersection()
	{
		frame();
		rotate([0,0,ang])
			translate([0,0,-duct_d/2])
				cube([duct_d*2, duct_d*2, duct_d]);
	}
}


module duct()
{
	color("blue")
		translate([0,0,50])
			cylinder(r = duct_d/2, h=20, $fn=200);
}

module frame()
{
	difference()
	{
		cube([duct_d+(big_gap+edge)*2, duct_d+(big_gap+edge)*2, 3*thick], center=true);
		cube([duct_d+big_gap*2, duct_d+big_gap*2, 5*thick], center=true);
	
		for(x=[-1,1])	for(y=[-1,1])
			translate([x*(duct_d/2+edge-big_gap), y*(duct_d/2+edge-big_gap), 0])
				cylinder(r = 3, h=50, $fn=20, center=true);
	
		translate([0,0,3*thick/2])
		difference()
		{
			cube([duct_d+(big_gap+edge-thick)*2, duct_d+(big_gap+edge-thick)*2, 4*thick], 
				center=true);
			cube([duct_d+(big_gap+thick)*2, duct_d+(big_gap+thick)*2, 5*thick], 
				center=true);
			for(x=[-1,1])	for(y=[-1,1])
			{
				translate([x*(duct_d/2+edge-big_gap), y*(duct_d/2+edge-big_gap), 0])
					cube([4*thick, 4*thick, 20*thick], center=true);
			}
			for(x=[-1,1])
				translate([x*(duct_d/2+edge-big_gap), 0, 0])
					cube([4*thick, 4*thick, 20*thick], center=true);
			for(y=[-1,1])
				translate([0, y*(duct_d/2+edge-big_gap), 0])
					cube([4*thick, 4*thick, 20*thick], center=true);
		}
		all_flaps(true, ang=6);
		for(x=[-1,1])
			translate([x*(duct_d/2+edge-big_gap), 0, 0.5*thick])
				rotate([90,0,0])
					cylinder(r=M3_rad, h = 5*thick, center=true, $fn = 30);
		for(y=[-1,1])
			translate([0, y*(duct_d/2+edge-big_gap), 0.5*thick])
				rotate([0,90,0])
					cylinder(r=M3_rad, h = 5*thick, center=true, $fn = 30);
	}
}

module flap_tab_hole(rad=M3_rad)
{
	translate([duct_d+(big_gap-small_gap)*2+1.5*thick,0,0])
						rotate([0,-90,0])
							cylinder(r=rad,h=duct_d+(big_gap-small_gap)*2+3*thick,centre=
								true,$fn=30);
}

module flap(rods=false, ang = 6)
{
	
	translate([-(duct_d/2+big_gap-small_gap),thick,thick+1-thick*0.7])
	rotate([-ang,0,0])
	{
		if(rods)
		{
			flap_tab_hole(M3_rad);
		} else
		{
			intersection()
			{
				difference()
				{
					translate([0,-thick,-thick-1])
					union()
					{
						cube([duct_d+(big_gap-small_gap)*2, thick+(duct_d+(big_gap-
							small_gap)*2)/n_flaps, flap_thick]);
						difference()
						{
							union()
							{
								cube([duct_d+(big_gap-small_gap)*2, 2*thick, 2*thick]);
								translate([duct_d/2+(big_gap-small_gap)-thick,0,0])
									cube([2*thick, 
										(duct_d+(big_gap-small_gap)*2)/n_flaps-thick, 2*thick]);
							}
							translate([2*thick,-1,0])
								cube([duct_d/2+(big_gap-small_gap)-4*thick, 4*thick, 4*thick]);
							translate([2*thick+duct_d/2+(big_gap-small_gap),-1,0])
								cube([duct_d/2+(big_gap-small_gap)-4*thick, 4*thick, 4*thick]);
							
						}
					}
					flap_tab_hole(M3_rad);
				}
				 union()
				{
					translate([0,0,-1])
						flap_tab_hole(5);
					translate([0,duct_d/2,0])
					cube([3*duct_d, duct_d, 15], center=true);
				}
			}
		}
	}
}

module all_flaps(rods=false, ang=6)
{
	for(i=[0:n_flaps-1])
	{
		translate([0, i*(duct_d+(big_gap-small_gap)*2)/n_flaps-(duct_d/2+big_gap-
			small_gap), 0])	flap(rods, ang);
	}
}
