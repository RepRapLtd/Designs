#
# FreeCAD Python Macro to Make an Air Vent
#
# Written by GPT4o
# (With a little help from Adrian Bowyer)
#
# RepRap Ltd
# https://reprapltd.com
#
# 9 August 2024
#
# Licence: GPL



# Define the air vent's parameters

length = 100        # Length of the vent
height = 50         # Height of the vent
thickness = 3       # Thickness of the vent
diameter = 5        # Diameter of the screw holes
edge_gap = 6       # Distance from the edge to the center of the screw holes
slots = 5            # Number of slots
slot_height = 4     # Height of each slot (in the Y/height direction)
louver_angle = 45  # Angle of the louvers in degrees

import FreeCAD as App
import Part
import math

# Calculate derived parameters
hole_radius = diameter / 2

# Create the main block
block = Part.makeBox(length, height, thickness)

# Create the cylindrical holes
hole_positions = [
    (edge_gap, edge_gap, 0),
    (length - edge_gap, edge_gap, 0),
    (edge_gap, height - edge_gap, 0),
    (length - edge_gap, height - edge_gap, 0)
]

holes = []
for pos in hole_positions:
    hole = Part.makeCylinder(hole_radius, thickness)
    hole.translate(App.Vector(pos))
    holes.append(hole)

# Cut the holes from the block
for hole in holes:
    block = block.cut(hole)

# Calculate the width of the slots with the additional edge_gap on both sides
slot_width = length - 4 * edge_gap

# Calculate the spacing between the slots
slot_spacing = (height - 2 * edge_gap - slots * slot_height) / (slots - 1)

# Create the slots with the adjusted width and position
slots_list = []
louvers_list = []
for i in range(slots):
    slot_y = edge_gap + i * (slot_height + slot_spacing)
    
    # Create the slot
    slot = Part.makeBox(slot_width, slot_height, thickness)
    slot.translate(App.Vector(2 * edge_gap, slot_y, 0))
    slots_list.append(slot)
    
    # Create the louver as a rectangular box, then rotate and position it
    louver_length = slot_width
    louver_thickness = thickness / math.sqrt(2)  # Adjust louver thickness for the rotation
    louver = Part.makeBox(louver_length, louver_thickness, slot_height + 3*louver_thickness)
    
    # Rotate the louver 45 degrees around the X-axis
    louver.rotate(App.Vector(0, 0, 0), App.Vector(1, 0, 0), louver_angle)
    
    # Position the louver at the top of the slot
    #louver.translate(App.Vector(2 * edge_gap, slot_y + slot_height, thickness - louver_thickness / 2))
    louver.translate(App.Vector(2 * edge_gap, slot_y + slot_height + thickness, 0))

    louvers_list.append(louver)

# Cut the slots from the block
for slot in slots_list:
    block = block.cut(slot)

# Add the louvers to the block
for louver in louvers_list:
    block = block.fuse(louver)

# Add the block with holes, slots, and louvers to the document
doc = App.ActiveDocument
if doc is None:
    doc = App.newDocument()

part_obj = doc.addObject("Part::Feature", "BlockWithHolesSlotsAndLouvers")
part_obj.Shape = block

# Recompute the document to update the view
doc.recompute()
