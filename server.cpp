#include <pthread.h>
#include "client_wss.hpp"
#include "server_wss.hpp"
#include <future>

#include "requestProcessing.hpp"

using namespace std;

using WssServer = SimpleWeb::SocketServer<SimpleWeb::WSS>;

int main() {
  // WebSocket Secure (WSS)-server at port 8080 using 1 thread
  WssServer server("server.crt", "server.key");
  server.config.port = 8080;

  auto &echo = server.endpoint["^/echo/?$"];

  echo.on_message = [](shared_ptr<WssServer::Connection> connection, shared_ptr<WssServer::InMessage> in_message) {
    auto out_message = in_message->string();

    cout << "Server: Message received: \"" << out_message << "\" from " << connection.get() << endl;


	out_message = processRequest(out_message);
	
	cout << "Server: Sending message \"" << out_message << "\" to " << connection.get() << endl;

	// connection->send is an asynchronous function
	connection->send(out_message, [](const SimpleWeb::error_code &ec) {
	if(ec) {
		cout << "Server: Error sending message. " <<
			// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
			"Error: " << ec << ", error message: " << ec.message() << endl;
	}
	});

    // Alternatively use streams:
    // auto out_message = make_shared<WssServer::OutMessage>();
    // *out_message << in_message->string();
    // connection->send(out_message);
  };

  echo.on_open = [](shared_ptr<WssServer::Connection> connection) {
    cout << "Server: Opened connection " << connection.get() << endl;
  };

  // See RFC 6455 7.4.1. for status codes
  echo.on_close = [](shared_ptr<WssServer::Connection> connection, int status, const string & /*reason*/) {
    cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
  };

  // Can modify handshake response header here if needed
  echo.on_handshake = [](shared_ptr<WssServer::Connection> /*connection*/, SimpleWeb::CaseInsensitiveMultimap & /*response_header*/) {
    return SimpleWeb::StatusCode::information_switching_protocols; // Upgrade to websocket
  };

  // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
  echo.on_error = [](shared_ptr<WssServer::Connection> connection, const SimpleWeb::error_code &ec) {
    cout << "Server: Error in connection " << connection.get() << ". "
         << "Error: " << ec << ", error message: " << ec.message() << endl;
  };

  

  // Start server and receive assigned port when server is listening for requests
  promise<unsigned short> server_port;
  thread server_thread([&server, &server_port]() {
    // Start server
    server.start([&server_port](unsigned short port) {
      server_port.set_value(port);
    });
  });
  cout << "Server listening on port " << server_port.get_future().get() << endl << endl;

  server_thread.join();
}
