@tool
extends Node

const DRAW_SCALE: float = 1.0
const CAM_WIDTH: int = 1152
const CAM_HEIGHT: int = 648

func _ready():
	var voronoi: Voronoi = Voronoi.new()
	var points = PackedVector2Array()
	
	var vector_array = []
	points.resize(100)
	
	var max_x = 0
	var max_y = 0
	for i in range(100):
		var x = randf() * CAM_WIDTH
		var y = randf() * CAM_HEIGHT
		points[i] = Vector2(x, y)
		max_x = x if x > max_x else max_x
		max_y = y if y > max_y else max_y
	
	var bounds: Rect2 = Rect2(0, 0, max_x, max_y)
	voronoi.initialize(points, bounds)
	var sites = voronoi.get_sites()
	
	for site in sites:
		var graph_line = Line2D.new()
		graph_line.width = 5
		graph_line.default_color = Color.RED
		var polygon_points = PackedVector2Array()
		
		for graph_edge in site.get_edges():
			var v1 = graph_edge.get_first_vertex()
			v1 = Vector2(snappedf(v1.x, 0.01), snappedf(v1.y, 0.01))
			var v2 = graph_edge.get_second_vertex()
			v2 = Vector2(snappedf(v2.x, 0.01), snappedf(v2.y, 0.01))
			
			if not v1 in polygon_points:
				prints('1:', graph_edge.get_first_vertex())
				polygon_points.append(v1)
			if not v2 in polygon_points:
				prints('2:', graph_edge.get_second_vertex())
				polygon_points.append(v2)
			
			graph_line.add_point(graph_edge.get_first_vertex() * DRAW_SCALE)
			graph_line.add_point(graph_edge.get_second_vertex() * DRAW_SCALE)
		print('-------------')
		
		var graph_polygon = Polygon2D.new()
		graph_polygon
		graph_polygon.polygon = polygon_points
		print(len(polygon_points))
		add_child(graph_polygon)
		add_child(graph_line)
		
