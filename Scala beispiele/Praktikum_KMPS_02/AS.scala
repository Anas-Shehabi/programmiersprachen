package P2_KMPS

import java.io.IOException
import scala.io.Source


case class Track(title: String, length: String, rating: Int, features: List[String], writers: List[String]) {
  override def toString: String = "\n\t\tTrack:\n\t\t\tTitle:" + title + "\n\t\t\tLength:" + length + "\n\t\t\tRating:" + rating + "\n\t\t\tFeatures:" + features.toString+ "\n\t\t\tWriters:" + writers.toString
}

case class Album(title: String, date: String, artist: String, tracks: List[Track]) {
  override def toString: String = "\n\tAlbum:\t\n\tTitle:" + title + "\t\n\tDate:" + date + "\t\n\tArtist:" + artist + "\n\tTracks:" + tracks.toString
}


object Funktional1 {

  def createTokenList(char_list : List[Char],TokenList: List[String],pos : Int) : List[String] = pos match {
    case 1700 => return TokenList
    case _ => char_list(pos) match {
      case '\n' | '\r' | '\t' => createTokenList(char_list,TokenList, pos+1)
      case '<' => createTokenList(char_list, TokenList :+ (tag_lesen(char_list,"",pos)),pos+2+tag_lesen(char_list,"",pos).length)
      case _ => createTokenList(char_list, TokenList :+ (wort_lesen(char_list,"",pos)),pos+wort_lesen(char_list,"",pos).length)
    }

  }
  def tag_lesen(char_list : List[Char],wort : String,pos : Int) : String = char_list(pos) match{
    case '<' => tag_lesen(char_list, wort, pos+1)
    case '>' =>  return wort
    case _ => tag_lesen(char_list, wort.concat(char_list(pos).toString), pos+1)
  }
  def wort_lesen(char_list : List[Char],wort : String,pos : Int) : String = char_list(pos) match{
    case '<' =>  return wort
    case _ => wort_lesen(char_list, wort.concat(char_list(pos).toString), pos+1)
  }



  def parseFile(TokenList : List[String], pos : Int, album: List[Album]) : List[Album] = pos match {
    case 171  => return album
    case _ => TokenList(pos) match {
      case "album" => parseFile(TokenList, zaehler_album(TokenList,pos)+1 , album :+ ParseAlbum(TokenList,pos+1, Album("","","",Nil)))
    }
  }
  def ParseAlbum(TokenList: List[String], pos : Int, album: Album ): Album = TokenList(pos) match {
    case "title" => ParseAlbum(TokenList, pos + 3, album.copy(title = TokenList(pos + 1)))
    case "date" => ParseAlbum(TokenList, pos + 3, album.copy(date = TokenList(pos + 1)))
    case "artist" => ParseAlbum(TokenList, pos + 3, album.copy(artist = TokenList(pos + 1)))
    case "track" => ParseAlbum(TokenList, zaehler_track(TokenList,pos) +1, album.copy(tracks = album.tracks :+ parseTrack(TokenList,pos+1,Track("","",0,Nil,Nil))))
    case "/album" => return album
  }

  def parseTrack (Tokenlist : List[String],pos : Int,track : Track) : Track = Tokenlist(pos) match{

    case "title" => parseTrack(Tokenlist,pos+3,track.copy(title = Tokenlist(pos+1)))
    case "length" => parseTrack(Tokenlist,pos+3,track.copy(length = Tokenlist(pos+1)))
    case "rating" => parseTrack(Tokenlist,pos+3,track.copy(rating = Integer.parseInt(Tokenlist(pos+1))))
    case "feature" => parseTrack(Tokenlist,pos+3,track.copy(features = track.features :+ Tokenlist(pos+1)))
    case "writing" => parseTrack(Tokenlist,pos+3,track.copy(writers = track.writers :+ Tokenlist(pos+1)))
    case "/track" => return track
  }
  def zaehler_album(Tokenlist: List[String],pos : Int): Int = Tokenlist(pos) match{
    case "/album" => return pos
    case _ => return zaehler_album(Tokenlist,pos+1)
  }
  def zaehler_track(Tokenlist: List[String],pos : Int): Int = Tokenlist(pos) match{
    case "/track" => return pos
    case _ => return zaehler_track(Tokenlist,pos+1)
  }

  @throws[IOException]
  def main(args: Array[String]) : Unit = {

    val source = Source.fromFile("G:\\fh-Aachen\\SEMSTER 5\\KMPS\\fassbender\\Praktikum\\Praktikum_KMPS_02\\alben.xml").toList
    val TokenList = createTokenList(source,Nil,0)
    
    print(TokenList.length)
    println(TokenList)
    println(parseFile(TokenList,0,Nil))
   // val myTrack = new Track("track_titile","2,50 ",1,List("maher","mifsk"),List("jknfkjsn"))
    //val myAlbum = new Album("title1"," "," ",List(myTrack))
    // print(myAlbum)
  }
}
