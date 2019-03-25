def bi_search(array, x):
	if array[array.length / 2] == x:
		return True
	else if array.length = 1:
		return False
	else if array[array.length / 2] > x:
		return bi_search(array[:array.length / 2], x);
	else if array[array.length / 2] < x:
		return bi_search(array[array.length / 2:], x);