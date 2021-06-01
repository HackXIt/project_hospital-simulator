/* NOTE
This code was originally auto-generated with "DiUS/cser"
and then manually modified to fix loop-errors caused by our self-referencing linked-lists datastructures.
All of the primitive datatype (short, int, char, ...) functions are preserved as-is from the auto-generators.

Modified functions are marked with <ERROR_PRONE>
Un-Modified functions are marked with <AUTO_GENERATED>
*/

#include "serializer.h"

// <ERROR_PRONE>
int raw_store_struct_ListRows(const struct ListRows *val, raw_write_fn w, void *q)
{
	// Store count value = 2 bytes
	char _count = 0;
	int ret = raw_store_unsigned_short((unsigned short *)&val->count, w, q);
	if (ret != 0)
	{
		return ret;
	}
	// Let us assume, the data list can be traversed & everything will run smoothly
	// Of course it won't, but this already is hard as it is.
	Seat_t *current = val->start;
	if (current == NULL)
	{ // List is empty, nothing to be done.
		int ret = w(missing_byte, sizeof(uint8_t), q);
		return ret;
	}
	else
	{ // List is not-empty, traverse and write bytes
		while (_count <= MAX_ROWS)
		{
			int ret = raw_store_char(_count, w, q);			// Write seat-number as byte
			int ret = raw_store_struct_Seat(current, w, q); // Write seat-structure-info
			if (ret != 0)
			{
				return ret;
			}
			current = current->node.next;
			_count++;
		}
	}
	return 0;
}
int raw_load_struct_ListRows(struct ListRows *val, raw_read_fn r, void *q)
{
	{
		int ret = raw_load_unsigned_short((unsigned short *)&val->count, r, q);
		if (ret != 0)
			return ret;
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Seat *tmp_item = calloc(1, sizeof(struct Seat));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Seat(tmp_item, r, q);
			if (ret == 0)
				val->start = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Seat *tmp_item = calloc(1, sizeof(struct Seat));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Seat(tmp_item, r, q);
			if (ret == 0)
				val->last = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
int raw_store_struct_ListPersons(const struct ListPersons *val, raw_write_fn w, void *q)
{
	{
		{int ret = raw_store_unsigned_short((unsigned short *)&val->count, w, q);
	if (ret != 0)
		return ret;
}
}
{
	{int ret = raw_store_unsigned_short((unsigned short *)&val->countZivil, w, q);
if (ret != 0)
	return ret;
}
}
{
	uint8_t present = (val->start != 0);
	int ret = w(&present, sizeof(present), q);
	if (ret != 0)
		return ret;
	if (present)
	{
		int ret = raw_store_struct_Person((struct Person *)val->start, w, q);
		if (ret != 0)
			return ret;
	}
}
// {
// 	uint8_t present = (val->last != 0);
// 	int ret = w(&present, sizeof(present), q);
// 	if (ret != 0)
// 		return ret;
// 	if (present)
// 	{
// 		int ret = raw_store_struct_Person((struct Person *)val->last, w, q);
// 		if (ret != 0)
// 			return ret;
// 	}
// }
return 0;
}
int raw_load_struct_ListPersons(struct ListPersons *val, raw_read_fn r, void *q)
{
	{
		int ret = raw_load_unsigned_short((unsigned short *)&val->count, r, q);
		if (ret != 0)
			return ret;
	}
	{
		int ret = raw_load_unsigned_short((unsigned short *)&val->countZivil, r, q);
		if (ret != 0)
			return ret;
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Person *tmp_item = calloc(1, sizeof(struct Person));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Person(tmp_item, r, q);
			if (ret == 0)
				val->start = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Person *tmp_item = calloc(1, sizeof(struct Person));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Person(tmp_item, r, q);
			if (ret == 0)
				val->last = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
int raw_store_struct_Seat(const struct Seat *val, raw_write_fn w, void *q)
{

	{
		uint8_t present = (val->occupied != 0);
		int ret = w(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			int ret = raw_store_struct_Person((struct Person *)val->occupied, w, q);
			if (ret != 0)
				return ret;
		}
	}
	{
		{
			int ret = raw_store_struct_node_s((struct node_s *)&val->node, w, q);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
int raw_load_struct_Seat(struct Seat *val, raw_read_fn r, void *q)
{
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Person *tmp_item = calloc(1, sizeof(struct Person));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Person(tmp_item, r, q);
			if (ret == 0)
				val->occupied = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		int ret = raw_load_struct_node_s((struct node_s *)&val->node, r, q);
		if (ret != 0)
			return ret;
	}
	return 0;
}
int raw_store_struct_Person(const struct Person *val, raw_write_fn w, void *q)
{
	{
		{int ret = raw_store_char((char *)&val->arrival, w, q);
	if (ret != 0)
		return ret;
}
}
{
	uint8_t present = (val->first_name != 0);
	int ret = w(&present, sizeof(present), q);
	if (ret != 0)
		return ret;
	if (present)
	{
		for (size_t i = 0; (val->first_name) && ((i == 0) || (val->first_name[i - 1])); ++i)
		{
			int ret = raw_store_char((char *)&val->first_name[i], w, q);
			if (ret != 0)
				return ret;
		}
	}
}
{
	uint8_t present = (val->last_name != 0);
	int ret = w(&present, sizeof(present), q);
	if (ret != 0)
		return ret;
	if (present)
	{
		for (size_t i = 0; (val->last_name) && ((i == 0) || (val->last_name[i - 1])); ++i)
		{
			int ret = raw_store_char((char *)&val->last_name[i], w, q);
			if (ret != 0)
				return ret;
		}
	}
}
// {
// 	for (size_t i = 0; i < (2); ++i)
// 	{
// 		uint8_t present = (val->neighbour[i] != 0);
// 		int ret = w(&present, sizeof(present), q);
// 		if (ret != 0)
// 			return ret;
// 		if (present)
// 		{
// 			int ret = raw_store_struct_Person((struct Person *)val->neighbour[i], w, q);
// 			if (ret != 0)
// 				return ret;
// 		}
// 	}
// }
// {
// 	uint8_t present = (val->seat != 0);
// 	int ret = w(&present, sizeof(present), q);
// 	if (ret != 0)
// 		return ret;
// 	if (present)
// 	{
// 		int ret = raw_store_struct_Seat((struct Seat *)val->seat, w, q);
// 		if (ret != 0)
// 			return ret;
// 	}
// }
// {
// 	uint8_t present = (val->row != 0);
// 	int ret = w(&present, sizeof(present), q);
// 	if (ret != 0)
// 		return ret;
// 	if (present)
// 	{
// 		int ret = raw_store_struct_ListRows((struct ListRows *)val->row, w, q);
// 		if (ret != 0)
// 			return ret;
// 	}
// }
{
	{
		int ret = raw_store_struct_node_p((struct node_p *)&val->node, w, q);
		if (ret != 0)
			return ret;
	}
}
return 0;
}
int raw_load_struct_Person(struct Person *val, raw_read_fn r, void *q)
{
	{
		int ret = raw_load_char((char *)&val->arrival, r, q);
		if (ret != 0)
			return ret;
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			char *tmp = 0;
			size_t n = 0;
			size_t offs = 0;
			do
			{
				if (offs >= n)
				{
					if (n == 0)
						n = 2 * sizeof(char);
					tmp = (char *)realloc(tmp, n *= 2);
					if (!tmp)
						return -ENOMEM;
					memset((char *)tmp + n / 2, n / 2, 0);
				}
				int ret = raw_load_char((char *)&tmp[offs++], r, q);
				if (ret != 0)
				{
					free(tmp);
					return ret;
				}
			} while (tmp[offs - 1]);
			val->first_name = tmp;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			char *tmp = 0;
			size_t n = 0;
			size_t offs = 0;
			do
			{
				if (offs >= n)
				{
					if (n == 0)
						n = 2 * sizeof(char);
					tmp = (char *)realloc(tmp, n *= 2);
					if (!tmp)
						return -ENOMEM;
					memset((char *)tmp + n / 2, n / 2, 0);
				}
				int ret = raw_load_char((char *)&tmp[offs++], r, q);
				if (ret != 0)
				{
					free(tmp);
					return ret;
				}
			} while (tmp[offs - 1]);
			val->last_name = tmp;
		}
	}
	{
		for (unsigned i = 0; i < (2); ++i)
		{
			uint8_t present;
			int ret = r(&present, sizeof(present), q);
			if (ret != 0)
				return ret;
			if (present)
			{
				struct Person *tmp_item = calloc(1, sizeof(struct Person));
				if (!tmp_item)
					return -ENOMEM;
				int ret = raw_load_struct_Person(tmp_item, r, q);
				if (ret == 0)
					val->neighbour[i] = tmp_item;
				else
					free(tmp_item);
				if (ret != 0)
					return ret;
			}
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Seat *tmp_item = calloc(1, sizeof(struct Seat));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Seat(tmp_item, r, q);
			if (ret == 0)
				val->seat = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct ListRows *tmp_item = calloc(1, sizeof(struct ListRows));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_ListRows(tmp_item, r, q);
			if (ret == 0)
				val->row = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		int ret = raw_load_struct_node_p((struct node_p *)&val->node, r, q);
		if (ret != 0)
			return ret;
	}
	return 0;
}
int raw_store_struct_node_s(const struct node_s *val, raw_write_fn w, void *q)
{
	// {
	// 	uint8_t present = (val->next != 0);
	// 	int ret = w(&present, sizeof(present), q);
	// 	if (ret != 0)
	// 		return ret;
	// 	if (present)
	// 	{
	// 		int ret = raw_store_struct_Seat((struct Seat *)val->next, w, q);
	// 		if (ret != 0)
	// 			return ret;
	// 	}
	// }
	// {
	// 	uint8_t present = (val->prev != 0);
	// 	int ret = w(&present, sizeof(present), q);
	// 	if (ret != 0)
	// 		return ret;
	// 	if (present)
	// 	{
	// 		int ret = raw_store_struct_Seat((struct Seat *)val->prev, w, q);
	// 		if (ret != 0)
	// 			return ret;
	// 	}
	// }
	return 0;
}
int raw_load_struct_node_s(struct node_s *val, raw_read_fn r, void *q)
{
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Seat *tmp_item = calloc(1, sizeof(struct Seat));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Seat(tmp_item, r, q);
			if (ret == 0)
				val->next = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Seat *tmp_item = calloc(1, sizeof(struct Seat));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Seat(tmp_item, r, q);
			if (ret == 0)
				val->prev = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
int raw_store_struct_node_p(const struct node_p *val, raw_write_fn w, void *q)
{
	// {
	// 	uint8_t present = (val->next != 0);
	// 	int ret = w(&present, sizeof(present), q);
	// 	if (ret != 0)
	// 		return ret;
	// 	if (present)
	// 	{
	// 		int ret = raw_store_struct_Person((struct Person *)val->next, w, q);
	// 		if (ret != 0)
	// 			return ret;
	// 	}
	// }
	// {
	// 	uint8_t present = (val->prev != 0);
	// 	int ret = w(&present, sizeof(present), q);
	// 	if (ret != 0)
	// 		return ret;
	// 	if (present)
	// 	{
	// 		int ret = raw_store_struct_Person((struct Person *)val->prev, w, q);
	// 		if (ret != 0)
	// 			return ret;
	// 	}
	// }
	return 0;
}
int raw_load_struct_node_p(struct node_p *val, raw_read_fn r, void *q)
{
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Person *tmp_item = calloc(1, sizeof(struct Person));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Person(tmp_item, r, q);
			if (ret == 0)
				val->next = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	{
		uint8_t present;
		int ret = r(&present, sizeof(present), q);
		if (ret != 0)
			return ret;
		if (present)
		{
			struct Person *tmp_item = calloc(1, sizeof(struct Person));
			if (!tmp_item)
				return -ENOMEM;
			int ret = raw_load_struct_Person(tmp_item, r, q);
			if (ret == 0)
				val->prev = tmp_item;
			else
				free(tmp_item);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
int raw_store_unsigned_short(const unsigned short *val, raw_write_fn w, void *q)
{
	unsigned short tmp = *val;
	uint8_t bytes[sizeof(unsigned short)];
	for (unsigned i = 1; i <= sizeof(unsigned short); ++i)
	{
		bytes[sizeof(unsigned short) - i] = (uint8_t)(tmp & 0xff);
		tmp >>= 8;
	}
	return w(bytes, sizeof(unsigned short), q);
}
int raw_load_unsigned_short(unsigned short *val, raw_read_fn r, void *q)
{
	uint8_t bytes[sizeof(unsigned short)];
	int ret = r(bytes, sizeof(unsigned short), q);
	if (ret != 0)
		return ret;
	unsigned short tmp = 0;
	for (unsigned i = 0; i < (sizeof(unsigned short)); ++i)
		tmp = (unsigned short)((tmp << 8) | bytes[i]);
	*val = tmp;
	return 0;
}
int raw_store_char(const char *val, raw_write_fn w, void *q)
{
	char tmp = *val;
	uint8_t bytes[sizeof(char)];
	for (unsigned i = 1; i <= sizeof(char); ++i)
	{
		bytes[sizeof(char) - i] = (uint8_t)(tmp & 0xff);
		tmp >>= 8;
	}
	return w(bytes, sizeof(char), q);
}
int raw_load_char(char *val, raw_read_fn r, void *q)