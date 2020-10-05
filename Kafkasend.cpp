using KafkaNet;
using KafkaNet.Model;
using KafkaNet.Protocol;

static void Main(string[] args) {
    string payload ="Welcome to Kafka!";
    string topic ="IDGTestTopic";
    Message msg = new Message(payload);
    Uri uri = new Uri(“http://localhost:9092”);
    var options = new KafkaOptions(uri);
    var router = new BrokerRouter(options);
    var client = new Producer(router);
    client.SendMessageAsync(topic, new List<Message> { msg }).Wait();
    Console.ReadLine();
}
