XML xml;

String agency = "ttc";
String route = "510";
String stopId = "11986"; // Spadina streetcar northbound at Nassau
String endpoint;

void setup() {
  endpoint = "https://retro.umoiq.com/service/publicXMLFeed?command=predictions&a=" + agency + "&r=" + route + "&stopId=" + stopId;
  println("Using " + endpoint);
}

void draw() {
  /* Get get the XML result. It'll look something like this:
  
  <body copyright="All data copyright Toronto Transit Commission 2022.">
    <predictions agencyTitle="Toronto Transit Commission" routeTitle="510-Spadina" routeTag="510" stopTitle="Spadina Ave At Nassau St" stopTag="6577">
      <direction title="North - North - 510 Spadina towards Spadina Station">
        <prediction epochTime="1642269218884" seconds="53" minutes="0" isDeparture="false" branch="510" dirTag="510_1_510A" vehicle="4539" block="510_8_80" tripTag="43503451"/>
        <prediction epochTime="1642269305979" seconds="140" minutes="2" isDeparture="false" branch="510" dirTag="510_1_510B" vehicle="4414" block="510_26_260" tripTag="43503529"/>
        <prediction epochTime="1642269447152" seconds="281" minutes="4" isDeparture="false" branch="510" dirTag="510_1_510B" vehicle="4404" block="510_27_270" tripTag="43503530"/>
        <prediction epochTime="1642269564122" seconds="398" minutes="6" isDeparture="false" branch="510" dirTag="510_1_510A" vehicle="4450" block="510_9_90" tripTag="43503452"/>
        <prediction epochTime="1642269913944" seconds="748" minutes="12" isDeparture="false" branch="510" dirTag="510_1_510B" vehicle="4429" block="510_20_200" tripTag="43503531"/>
      </direction>
    </predictions>
  </body>
  
  ...so we need to drill down through predictions, direction, prediction,
  then get the "seconds" attribute of the fist prediction
  */
  
  xml = loadXML(endpoint);
  XML[] predictions = xml.getChildren("predictions");

  // results come back as an array (even if there's only 1 child), so we need to always get the first element of the array:
  
  XML[] direction = predictions[0].getChildren("direction");

  XML[] prediction = direction[0].getChildren("prediction");

  // use the first prediction, which will be soonest:
  
  int seconds = prediction[0].getInt("seconds");
  
  println("Next bus in " + seconds + " seconds.");
  
  // Hey - why not publish this number to shiftr.io?

  delay(3000);
}
