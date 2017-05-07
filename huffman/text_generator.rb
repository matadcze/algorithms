file = File.open("sample.txt", "w+")
3141516.times { file.print(rand(65..90).chr) }