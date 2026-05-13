-module(whatsapp_client_process).
-export([start/0, loop/0]).

start() ->
    spawn(?MODULE, loop, []).

loop() ->
    receive
        {send_message, To, EncryptedPayload} ->
            io:format("Routing msg to ~p: ~p~n", [To, EncryptedPayload]),
            loop();
        {receive_ack, MsgId} ->
            io:format("Message ~p delivered. Deleting from RAM.~n", [MsgId]),
            loop();
        disconnect ->
            io:format("Client disconnected. Terminating process.~n"),
            ok;
        _Other ->
            io:format("Unknown packet received.~n"),
            loop()
    end.
