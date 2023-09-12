---- MODULE Scheduler ----------------------------------------------------------
(* Scheduler Specification is a Non-Interleaving Specification. *)
--------------------------------------------------------------------------------
EXTENDS Channel, Sequences
VARIABLES p_seq,
          p_seq_maxlen,
          ctl,
          progin,
          exin,
          exout
CONSTANTS Resource,
          CMD,
          Serializable

Program == [Requirements: Resources, Command: Seq(CMD)]
ProgChan == INSTANCE Channel WITH data <- Program, chan <- progin

Message == [type: {"ResourceQuery", "Eval"}, content: Serializable]
InExChan  == INSTANCE Channel WITH data <- Message, chan <- exin
outExChan == INSTANCE Channel WITH data <- Message, chan <- exout

(* Request from environment this step will*)
(* append the request to sequence *)
ProgReq(prog) == /\ ProgChan!Rcv (* Assert that pq is not full *)
                 /\ Len(p_seq) # p_seq_maxlen
                 /\ p_seq' = Append(p_seq, progin.val) (* Update status of pq *)

(* Select ExecuteGroup to run program*)
(* from the head of Sequence pq *)
Select == /\ pq # <<>> (* Program Sequence not empty *)
                   /\ LET current == HEAD(pq)
                      IN                        (* *)



--------------------------------------------------------------------------------
================================================================================
