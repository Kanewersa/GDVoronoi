@tool
extends Node

const DRAW_SCALE: float = 1.0
const CAM_WIDTH: int = 1152
const CAM_HEIGHT: int = 648

const POINT = preload("res://point.tscn")

func _ready():
	var voronoi: Voronoi = Voronoi.new()
	var points = PackedVector2Array()
	
	var vector_array = []
	points.resize(100)
	
	for i in range(100):
		var x = snappedf(randf() * CAM_WIDTH, 0.01)
		var y = snappedf(randf() * CAM_HEIGHT, 0.01)
		points[i] = Vector2(x, y)
	
	var bounds: Rect2 = Rect2(0, 0, CAM_WIDTH, CAM_HEIGHT)
	voronoi.initialize(points, bounds)
	var sites = voronoi.get_sites()
	
	for site in sites:
		var graph_line = Line2D.new()
		graph_line.width = 2
		graph_line.default_color = Color.BLUE
		var polygon_points = PackedVector2Array()
		
		for graph_edge in site.get_edges():
			var v1 = graph_edge.get_first_vertex()
			polygon_points.append(v1)
			graph_line.add_point(v1 * DRAW_SCALE)
		
		var graph_polygon = Polygon2D.new()
		graph_polygon.polygon = polygon_points
		add_child(graph_polygon)
		add_child(graph_line)
		
		for graph_edge in site.get_edges():
			var point = POINT.instantiate()
			point.position = graph_edge.get_first_vertex()
			add_child(point)
