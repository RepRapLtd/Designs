module box(x = 10, y = 20, z = 30, center = false)
{
	scale([x,y,z])
	{
		cube(1, center = center);
	}
}

module cone(radius = 10, height = 20, center = false)
{
	cylinder(height, radius, 0, center = center);
}

module tube(outer = 20, inner = 10, height = 100, center = false)
{
	difference()
	{
		cylinder(r = outer, h = height, center = center);
		cylinder(r = inner, h = height, center = center);
	}
}

module pyramid(width = 20, height = 20)
{
	polyhedron(
		points = [
			[width, 0, 0],
			[0, width, 0],
			[-width, 0, 0],
			[0, -width, 0],
			[0, 0, height]
		],
		triangles = [
			[0, 1, 2, 3],
			[4, 1, 0],
			[4, 2, 1],
			[4, 3, 2],
			[4, 0, 3]
		]
	);
}

module wedge(width = 10, height = 20, depth = 30)
{
	rotate([0, -90, 0])
	{
	polyhedron(
		points = [
			[0, 0, 0],
			[height, 0, 0],
			[0, width, 0],
			[0, 0, depth],
			[height, 0, depth],
			[0, width, depth]
		],
		triangles = [
			[0,1,2],
			[5,4,3],
			[3,4,1,0],
			[0,2,5,3],
			[4,5,2,1]
		]
	);
	}
}

module cross(width = 30, thickness = 10, depth = 5)
{
	union()
	{
		box(thickness, width, depth, center = true);
		box(width, thickness, depth, center = true);
	}
}

module wineglass()
{
	module halfstem()
	{
		intersection()
		{
			cylinder(40, 10, 5);
			translate([0,0,20])
			{
				cross(20, 5, 40);
			}
		}
	}

	module stem()
	{
		union()
		{
			halfstem();

			translate([0, 0, 40*2-1])
			{
				rotate([180, 0, 0])
				{
					halfstem();
				}
			}
		}
	}

	module cup()
	{
		scale([1,1,1.3])
		{
			difference()
			{
				sphere(25);
				translate([0, 0, 40])
				{
					cube(50, true);
				}
			}
		}
	}

	module base()
	{
		cylinder(4, 20, 20);
	}

	module main()
	{
		difference()
		{
			union()
			{
				translate([0,0,40*2.4])
				{
					cup();
				}		
				stem();
				base();
			}
			translate([0, 0, 40*2.4])
			{
				scale([1,1,1.3])
				{
					sphere(24);
				}
			}
		}
	}

	main();
}

wineglass();