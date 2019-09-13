$fn=60;

difference()
{
	union()
	{
			cylinder(r=1.2+10.5/2,h=61);
			translate([0,0,61])
				cylinder(r1=1.2+10.5/2,r2=0,h=1.2+10.5/2);			
	}

	cylinder(r=10.5/2,h=60);
	cylinder(r=11.15/2,h=20.7);
	cylinder(r=11.55/2,h=16.5);

	translate([0,0,60])
		cylinder(r1=10.5/2,r2=0,h=10.5/2);
}
