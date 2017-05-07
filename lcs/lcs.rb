# -*- coding: utf-8 -*-

require 'set'

class LCS
  Infinity = 1.0/0.0

  def initialize(s1, s2)
    @s1, @s2 = s1, s2
    @c = Array.new(@s1.length + 1) { Array.new(@s2.length + 1, 0) }
    @b = Array.new(@s1.length + 1) { Array.new(@s2.length + 1, '0') }
  end

  def lcs_length
    1.upto(@s1.length) do |i| 1.upto(@s2.length) do |j| 
        if @s1[i - 1] == @s2[j - 1]
          @c[i][j] = @c[i - 1][j - 1] + 1
          @b[i][j] = "\\"
        else
          if @c[i - 1][j] >= @c[i][j - 1]
            @c[i][j] = @c[i - 1][j]
            @b[i][j] = "|"
          else
            @c[i][j] = @c[i][j - 1]
            @b[i][j] = "-"
          end
        end
      end
    end
    @c[@s1.length][@s2.length]
  end
  
  def print_graph ; @b.each { |line| puts line.join(' ') } ; end
  def print_numbers ; @c.each { |line| puts line.join(' ') } ; end
  
  def print_lcs(i, j)
    $x = ""
    return $x if i == 0 || j == 0
    if @b[i][j] == "\\"
      print_lcs(i - 1, j - 1)
      $x += @s1[i - 1]
    else 
      if @b[i][j] == "|"
        print_lcs(i - 1, j)
      else
        print_lcs(i, j - 1)
      end
    end
  end
  
  def print_all_lcs(i, j)
    return Set.new([""]) if i == 0 || j == 0
    if @s1[i - 1] == @s2[j - 1]
      x = print_all_lcs(i - 1, j - 1).flat_map { |z| "#{z}#{@s1[i - 1]}" }
      return Set.new([x].flatten)
    else
      r = Set.new([])
      r.merge(print_all_lcs(i, j-1)) if @c[i][j-1] >= @c[i-1][j]
      r.merge(print_all_lcs(i-1, j)) if @c[i-1][j] >= @c[i][j-1]
      return r
    end
  end
  
  def lcs_rec
    1.upto(@s1.length) { |i| 1.upto(@s2.length) { |j| @c[i][j] = Infinity } }
    lcs_lookup(@s1.length, @s2.length)
  end
  
  def lcs_lookup(i, j)
    return @c[i][j] if @c[i][j] < Infinity
    if @s1[i - 1] == @s2[j - 1]
      @c[i][j] = lcs_lookup(i - 1, j - 1) + 1
      @b[i][j] = "\\"
    else
      c1 = lcs_lookup(i - 1, j)
      c2 = lcs_lookup(i, j - 1)
      if c1 >= c2
        @c[i][j] = c1
        @b[i][j] = "|"
      else
        @c[i][j] = c2
        @b[i][j] = "-"
      end
    end
    return @c[i][j]
  end
end

#s1, s2 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA", "GTCGTTCGGAATGCCGTTGCTCTGTAAA"
#s1, s2 = "AGCAT", "GAC"
s1, s2 = "POLITECHNIKA", "TOALETA"
# s1, s2 = "abaabbaaa", "babab"
# s1, s2 = "aabbcc", "abacb"
# s1, s2 = "asdfghj", "addfgcxd"
# s1, s2 = "123", "543"
s1, s2 = "aabbcc", "abacb"

l = LCS.new(s1, s2)
len = l.lcs_length # l.lcs_length
puts "The longest common subsequence has #{len} element(s)."
puts "One of LCS's is \'#{l.print_lcs(s1.length, s2.length)}\'"
l.print_graph
puts ""
l.print_numbers
puts "All the longest common subsequence:"
l.print_all_lcs(s1.length, s2.length).each { |sub| puts "> #{sub}" }

# l = LCS.new(s1, s2)
# len = l.lcs_rec # l.lcs_length
# puts "The longest common subsequence has #{len} element(s)."
# puts "One of LCS's is \'#{l.print_lcs(s1.length, s2.length)}\'"
# l.print_graph
# puts ""
# l.print_numbers
# puts "All the longest common subsequence:"
# l.print_all_lcs(s1.length, s2.length).each { |sub| puts "> #{sub}" }
