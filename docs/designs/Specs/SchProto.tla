(* Protocol that change datas between Scheduler and ExecGroup *)
---- MODULE SchProto -----------------------------------------------------------
CONSTANTS MsgContent
VARIABLES inchan, (* Channel to transfer datas between Scheduler and ExecGroup *)
          outchan,
          ctl,
          data

    ---- MODULE Message --------------------------------------------------------
    CONSTANTS Content

    Msg == [type: {"resq", "resp", "progeval", "progrep"},
               content: Content]
    Type(m) == m.type
    ContentData(m) == m.content
    ============================================================================

SchInit == /\ ctl = "rdy"

I == INSTANCE Message WITH Content <- MsgContent

InChan == INSTANCE Channel WITH Data <- I!Msg, chan <- inchan
OutChan == INSTANCE Channel WITH Data <- I!Msg, chan <- outchan

ResQueryReq == /\ ctl = "rdy"
               /\ \E m \in I!Msg:
                 IF I!Type(m) = "resq"
                 THEN /\ OutChan!Send(m)
                      /\ ctl' = "busy"
                 ELSE ctl' = ctl

ResQueryRep == /\ ctl' = "busy"
               /\ ctl' = "rdy"
               /\ InChan!Rcv
               /\ LET reply == inchan.val
                  IN  data' = reply.content

================================================================================

