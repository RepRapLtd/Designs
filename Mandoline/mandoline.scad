thick=2.2;
xl=154;
yl=78;
sl=102;
ch=7;
rad=6.5/2;

rotate([0,180,0])
union()
{
	difference()
	{
		cube([xl, yl, thick], center=true);
		translate([-40-xl/2+17,0,0])
		rotate([0,0,-atan2(xl-sl, yl)])
		cube([80, 200, 2*thick], center=true);
	}
	translate([xl/2-36.3-rad,-yl/2+6.75+rad,-thick/2-ch])
	cylinder(r=rad, h=ch, $fn=30);
}