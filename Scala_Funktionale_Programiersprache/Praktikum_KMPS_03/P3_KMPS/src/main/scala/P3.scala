
import Funktional1.{createTokenList, parseFile}
import P3.poly_map

import scala.io.Source
object P3 {

  def map[A](input_list: List[A], func: (A => A)): List[A] = input_list match {
    case Nil => Nil
    case x :: xs => func(x) :: map(xs, func)

  }

  def poly_map[A, B](input_list: List[A], func: (A => B)): List[B] = input_list match {
    case Nil => Nil
    case x :: xs => func(x) :: poly_map(xs, func)
  }


  def filter[A](input_liste:List[A],condition: (A=>Boolean)): List[A] = input_liste match {
    case Nil => Nil
    case x :: xs => condition (x) match {
      case true => x :: filter(xs,condition)
      case false => filter(xs,condition)
    }
  }


  def partition[A](input_list: List[A], condition: A => Boolean, zwischenspeichern: List[A]): List[List[A]] = input_list match {
    case Nil => zwischenspeichern :: Nil
    case x :: xs => condition(x) match {
      case true => zwischenspeichern :: partition[A](xs, condition, Nil)
      case false => partition(xs, condition, zwischenspeichern :+ x)
    }
  }

  def isBlank(s: String): Boolean = s.trim.isEmpty

  def createTokenList2(myInputXML: List[Char]): List[String] = {
    partition[Char](myInputXML, x => x == '<' | x == '>' | x == '\r' | x == '\t' | x == '\n', Nil) match {
      case x :: xs => isBlank(x.mkString) match {
        case true => filter[String](poly_map[List[Char], String](xs, x => x.mkString), x => x != "")
        case false => x.mkString :: filter[String](poly_map[List[Char], String](xs, x => x.mkString), x => x != "")
      }
    }
  }

  def createTokenList1(myInputXML: List[Char]): List[String] = {

    filter[String](poly_map[List[Char], String](partition[Char](myInputXML, x => x == '<' | x == '>' | x == '\r' | x == '\t' | x == '\n', Nil), x => x.mkString), x => x != "")
  }

  def prod(f: Int => Int, a: Int, b: Int): Int =
    if (a > b) 1 else f(a) * prod(f, a + 1, b)

  def sum(f: Int => Int, a: Int, b: Int): Int =
    if (a > b) 0 else f(a) + sum(f, a + 1, b)


  def range(a: Int, b: Int): List[Int] = if (a > b) Nil else a :: range(a + 1, b)

  def foldl(f: (Int, Int) => Int, start: Int, xs: List[Int]): Int = xs match {
    case x :: Nil => f(start, x) //bei leerer Liste Rückgabe von start
    case h :: ts => foldl(f, f(start, h), ts)
  }

 /* def allgemein(f: (Int => Int, Int, Int) => Int, g: Int => Int)(a: Int, b: Int): Int = {
    f(g, a, b)
  }*/

  def prod_sum_allgemein(a: Int, b: Int, start: Int, g: Int => Int, f: (Int, Int) => Int): Int =
    if (a > b) start
    else f(g(a), prod_sum_allgemein(a + 1, b, start, g, f))

  def allgemein_ohne_rekusion(f: (Int, Int) => Int, g: Int => Int)(a: Int, b: Int): Int = {
    foldl(f, g(a), map[Int](range(a + 1, b), g))
  }

  def main(args: Array[String]) : Unit = {
   println (map[Char]('a'::'b'::'c'::Nil, x => x.toUpper))
    val myChars = Source.fromFile("G:\\fh-Aachen\\SEMSTER 5\\KMPS\\fassbender\\Praktikum\\Praktikum_KMPS_02\\alben.xml").toList
    //println(myChars)
    val myTokenList = createTokenList(myChars, Nil, 0)
    //println(myTokenList)
    val fileRead = parseFile(myTokenList,0,Nil)
   // println(fileRead)
    val album_list_große_title = map[Album](fileRead, album => album.copy(title = album.title.toUpperCase))
    println(album_list_große_title)
    val album_list_große_track_title = map[Album](album_list_große_title, album => album.copy(tracks = map[Track](album.tracks, track => track.copy(title = track.title.toUpperCase))))
    println(album_list_große_track_title)
    val track_leange_liste = poly_map[Album,List[String]](fileRead,album => poly_map[Track,String](album.tracks,track => track.length))
    println(track_leange_liste)

    /* --------------------- Aufgabe 2 ---------------------------*/
    println("--------------------- Aufgabe 2 ---------------------------")
    /*-------------------------a------------------------------*/
    println(filter[Int](1::2::3::4::5::6::7::8::9::Nil,x=>x%2==0))

  //  val Erste_album = fileRead(0)
    val zweite_album = fileRead(1)
  //  println(Erste_album)
  //  println(zweite_album)

    /*-------------------------b------------------------------*/
    val allTracks = fileRead(0).tracks.toList.appendedAll(fileRead(1).tracks)
    //println(allTracks)
    val Tracks_mit_Bewertung_mehr_als_vier = filter[Track](allTracks,x=>x.rating >= 4)
    println(Tracks_mit_Bewertung_mehr_als_vier)
   // val Tracks_mit_Bewertung_mehr_als_vier2 = filter[Track](zweite_album.tracks,x=>x.rating >= 4)
   //println(Tracks_mit_Bewertung_mehr_als_vier2)

  //  val List_Title1 = poly_map[Album,List[String]](fileRead,album => filter[Track](album.tracks, x => x.writers == filter[String](x.writers, y => y == "Rod Temperton")), x => x.title)
  //val List_Title = filter[List[Track]](allTracks,track => track.rating >= 4)

  /*-------------------------c------------------------------*/
  val Tracks_von_Rod =poly_map[Track,String](filter[Track](allTracks,(x => x.writers == filter[String](x.writers,y=> y=="Rod Temperton") && x.writers != List()) ),x=>x.title)
    println(Tracks_von_Rod)

    /* --------------------- Aufgabe 3 ---------------------------*/
    println("--------------------- Aufgabe 3 ---------------------------")
    println(partition[Char]('a'::'b'::'c'::'D'::'e'::'f'::'G'::'H'::'i'::'J'::Nil,x=>x==x.toUpper,Nil))

    val Tracks_Title_ohne_Thriller = partition[Track](allTracks, x => x.title == "Thriller", Nil)
    println(Tracks_Title_ohne_Thriller)
    println(createTokenList1(myChars))
   // println(createTokenList2(myChars))



    /*______________________________________________*/

  //  println(partition[Char](myChars, x => x == '<' | x == '>' | x == '\r' | x == '\t' | x == '\n', Nil))

    //--------------------------------Aufgabe4----------------------------------//
    /*val test = verallgemeinert_Operation(x=>x,false)(1,5)
    println(test)*/
   // val mytest = allgemein(prod, x => x * x)(1, 5)
   // println(mytest)
    //println(foldl((x,y)=>x+y,1,1::2::3::4::Nil))
    val x = allgemein_ohne_rekusion((x, y) => x * y, x => x * x)(1, 5)
   // println(x)

    val x2 = prod_sum_allgemein(1,5,1,x => x * x,(x, y) => x * y)
   // println(x2)
    val sumtest = sum(x=>x,1,2)
   // println(sumtest)
    val range1= range(5,10)
   // println(range1)
  }

}