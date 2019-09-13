
//ring();

translate([0,0,20]) funnel();

module ring()
{
	difference()
	{
		cylinder(r=73/2, h=7, center=true, $fn=100);
		cylinder(r=63/2, h=20, center=true, $fn=100);
	   translate([0,0,5])
			cube([100, 23, 10], center=true);
	}
}

module funnel()
{
	union()
	{
		difference()
		{
			cylinder(r=63/2, h=3.5, center=true, $fn=100);
			cylinder(r=52/2, h=10, center=true, $fn=100);
		}
		translate([0,0,20+3/2])
		difference()
		{
			cylinder(r1=63/2, r2=63/2 + 40, h=40, center=true, $fn=100);
			cylinder(r1=50.9/2, r2=52/2 + 40, h=41, center=true, $fn=100);
		}
	}
}