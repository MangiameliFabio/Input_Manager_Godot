extends Node

var gras = preload("res://Assets/Gras.jpg")
var bush = preload("res://Assets/Busche.jpg")
var flower = preload("res://Assets/Gras_mit_Blume.jpg")
var big_stone = preload("res://Assets/Gras_mit_groen_Steinen.jpg")
var small_stone = preload("res://Assets/Gras_mit_Steinen.jpg")

var gridx = 0
var gridy = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	var rmg = RandomMapGenerator.new()
	var rule = Array()
	rule.append([0,0,1])
	rule.append([0,1,0])
	rule.append([1,0,0])
		
	rmg.add_new_object(5)
	rmg.add_new_object(2)
	rmg.add_new_object(10)
	rmg.add_new_object(1, rule)
	rmg.add_new_object(3)
	rmg.add_new_object(3)

	var array = rmg.get_generated_map(100,100)

	for row in array:
		for tile in row:
			var sprite = Sprite.new()
			sprite.set_texture(choseSprite(tile))
			sprite.position.x = gridx
			gridx += 64
			sprite.position.y = gridy	
			add_child(sprite)
		gridx = 0
		gridy += 64

func choseSprite(value):
	if value == 0:
		return gras
	if value == 1:
		return bush
	if value == 2:
		return flower
	if value == 3:
		return big_stone
	if value == 4:
		return small_stone
	if value == 5:
		return big_stone
	

