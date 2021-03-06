#include "../header/hpfem.h"

void htflush(HashTable* ht_elem_ptr, HashTable*  ht_node_ptr, int option)
{

  int i, j, k;
  Element*       EmTemp;
  Node*          NdTemp;
  unsigned       KeyTemp[KEYLENGTH];
  HashEntryPtr   entryp;
  unsigned*      keyP;
  void*          p;
  int*           dofP;
  double*        sol;
  int e_buckets=ht_elem_ptr->get_no_of_buckets();
  int n_buckets=ht_node_ptr->get_no_of_buckets();

  switch(option)
    {
    case 1:
      for(i=0;i<e_buckets;i++)
	{
	  entryp = *(ht_elem_ptr->getbucketptr() + i);
	  while(entryp)
	    { 
	      EmTemp = (Element*)(entryp->value);
	      EmTemp->put_new_old(OLD);
	      entryp = entryp->next;
	    }
	}
      break;
    case 2:
      for(i=0;i<n_buckets;i++)
	{
	  entryp = *(ht_node_ptr->getbucketptr() + i);
	  while(entryp)
	    { 
	      NdTemp = (Node*)(entryp->value);
	      //NdTemp->putinfo(INIT);
	      NdTemp->putdof(INIT,INIT );
	      NdTemp->putglnum(INIT);
	      NdTemp->put_reconstructed(0);

	      entryp = entryp->next;
	    }
	}
      for(i=0;i<e_buckets;i++)
	{
	  entryp = *(ht_elem_ptr->getbucketptr() + i);
	  while(entryp)
	    { 
	      EmTemp = (Element*)(entryp->value);
	      for(j=0;j<8;j++) {
		EmTemp->put_recv_flag(j, 0);
		EmTemp->put_send_flag(j, 0);
	      }
	      entryp = entryp->next;
	    }
	}
    }
}
