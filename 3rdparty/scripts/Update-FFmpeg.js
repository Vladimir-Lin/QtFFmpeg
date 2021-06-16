// This demo javascript is not completed
function CompressionFiles()
{ // Scriptable N::File is stiil not fully working
  var f = new File ( ) ;
  var msg = "Write to file" ;
  var filename = "E:/Temp/JavaWriteFile.txt" ;
    print ( "setFileName" ) ;
  f.setFilename ( filename ) ;
    print ( "open" ) ;
  f.open(2) ;
    print ( "close" ) ;
  f.close() ;
  delete f ;
}
