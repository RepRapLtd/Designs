cup_hole=66;
edge_thickness=6;
cone_angle=15;
tab_angle=10;

phone_w=67;
phone_t=11;
phone_angle=20;


delta=0.5*edge_thickness/cos(cone_angle);
inner_r = 0.5*cup_hole - delta;
outer_r=inner_r + 0.5*edge_thickness*tan(cone_angle);


disc();
phone_bracket();
//tab();
//tabs();
//demi_phone_bracket();

//phone_block(x=phone_w, y= phone_t, z=30, angle=phone_angle);

module phone_block(x=1, y= 1, z=1, angle=20)
{
	rotate([-angle,0,0])
	difference()
	{
		rotate([angle,0,0])
	  		cube([x, y, z], center=true);
		translate([0,0,-0.5*(z+cos(angle)*(z-y))])
			cube([10*x, 10*y, z], center=true);
	}
}

module demi_phone_bracket()
{
	rotate([90-phone_angle,0,0])
	intersection()
	{
		phone_bracket();
		translate([-50,0,0])
		rotate([phone_angle,0,0])
			translate([0,0,-10])
			  cube([100,100,100]);
	}
}

module phone_bracket()
{
translate([0,-4,11.75])
rotate([phone_angle,0,0])
difference()
{
	union()
	{
	phone_block(x=phone_w+4, y=phone_t+4, z=40, angle=phone_angle);
		translate([phone_w*0.4,0,-13.7])
			rotate([0,0,0])
				cube([phone_t*0.6, phone_t*1.363, 8], center=true);
		translate([-phone_w*0.4,0,-13.7])
			rotate([0,0,0])
				cube([phone_t*0.6, phone_t*1.363, 8], center=true);
	}
	translate([0,0,4])
			phone_block(x=phone_w, y=phone_t, z=40, angle=phone_angle);
	translate([0,phone_t*0.5,10])
			phone_block(x=phone_w-6, y=phone_t, z=40, angle=phone_angle);
	translate([0,0,0])
			phone_block(x=15, y=phone_t*0.6, z=60, angle=phone_angle);	
}


}

module disc()
{
difference()
{
translate([0,0,-1.5])
cylinder(r=outer_r+6,  h=3, center=true,$fn=200);
translate([0,0,-1.5])
cylinder(r=outer_r-10,  h=30, center=true,$fn=200);
tabs();
phone_bracket();
}

}

module tab()
{

translate([(cup_hole+edge_thickness*(1-1/cos(cone_angle)))*0.5 , 0, 0])
translate([0,0,edge_thickness*0.38])
rotate([0,0,-90])
difference()
{
translate([0,0,-edge_thickness*0.1])
cube([8,5,edge_thickness*1.6], center=true);


translate([-7.5,0,0])
rotate([-cone_angle,0,0])
cube([15,5,1.5*edge_thickness]);

translate([-7.5,0,0])
rotate([cone_angle,0,0])
translate([0,0,-1.5*edge_thickness])
cube([15,5,1.5*edge_thickness]);

translate([-7.5,0,0.75*edge_thickness])
rotate([cone_angle,0,0])
translate([0,0,-1.5*edge_thickness])
cube([15,5,1.5*edge_thickness]);

translate([-7.5,0.63,-1.5*edge_thickness])
cube([15,5,1.5*edge_thickness]);


}
}

module tabs()
{
union()
{
rotate([0,0,30])
tab();
rotate([0,0,150])
tab();
rotate([0,0,-90])
tab();
}
}

