$Port=9000

$endpoint = new-object System.Net.IPEndPoint ([ipaddress]::any,$Port)
$listener = new-object System.Net.Sockets.TcpListener $endpoint 
$listener.start()
while($true){
    $data = $listener.AcceptTcpClient()
    $stream = $data.GetStream() 
    $bytes = New-Object System.Byte[] 1024
    while (($i = $stream.Read($bytes,0,$bytes.Length)) -ne 0){
        $EncodedText = New-Object System.Text.ASCIIEncoding
        $data = $EncodedText.GetString($bytes,0, $i)
        Write-Output $data
    }
    $stream.close()
}
$listener.stop()