difference()
{
	union()
	{
		cube([19, 6, 7], center=true);
		translate([9.5,0,0])
			scale([0.6,1,1])
			cylinder(r=3, h=7, center=true, $fn=40);
		translate([-9.5,0,0])
scale([0.6,1,1])
			cylinder(r=3, h=7, center=true, $fn=40);

	}
	cube([18, 5, 20], center=true);
		translate([9.5,0,0])
scale([0.6,1,1])
			cylinder(r=2.5, h=20, center=true, $fn=40);
		translate([-9.5,0,0])
scale([0.6,1,1])
			cylinder(r=2.5, h=20, center=true, $fn=40);

}